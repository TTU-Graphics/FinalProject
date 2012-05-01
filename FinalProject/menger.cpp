#include "menger.h"

Menger::Menger(vec3 center, float radius, int subdivs) {//, ChainedModel *parent): ChainedModel(parent) {
  fShader = (char*)"color.frag";
  vShader = (char*)"color.vert";
  name = "Menger";

  computeVerticiesFn = &Menger::computeVerticies;
  subdivideFn = &Menger::subdivideMenger;
  curType = NORMAL;
  bufferCount = 2;
  cubeCenter = center;
  cubeRadius = radius;
  curSubdivisions = subdivs;
  init();
}
//{{{ compute verticies
int Menger::computeVerticies(int subdivisions) {
  int cubes = 1;
  for(int i=0;i<subdivisions;i++) {
    cubes *= 20;
  }
  int tris = cubes * 12;
  return tris * 3;
}

int Menger::computeInverseVerticies(int subdivisions) {
  int cubes = 0, mengerCubes=1;
  for(int i=0;i<subdivisions;i++) {
    cubes += mengerCubes*7;
    mengerCubes *= 20;
  }
  return cubes * 36;
}
//}}}
//{{{ buildFace()
/*
 * The face variable should be formatted the following way:
 *
 * 0--1
 * | /|
 * |/ |
 * 3--2
 */
void Menger::buildFace(vec4* face, int col) {
  static vec4 cols[] = {
    hexToVec4("FFFFFF",1.0),  //+y = white
    hexToVec4("00FF00",1.0),  //+x = green?
    hexToVec4("0000FF",1.0),  //-x = blue
    hexToVec4("FF6600",1.0),  //-z = orange?
    hexToVec4("FFFF00",1.0),  //-y = yellow
    hexToVec4("FF0000",1.0),  //+z = red
  };

  buildTri(points, index, face[0], face[1], face[3]);
  buildTri(points, index+3, face[1], face[2], face[3]);

  //set colors and incrase index by 6
  for(int i=0; i<6; i++) {
    colors[index++] = cols[col];
  }
}
//}}}
//{{{ buildCube()
/**
 * This will build the 8 points of a cube given:
 *
 * vec4 cube - the center point of a cube
 * float radius - the distance from the center point to a corner on the cube
 *
 * The cube will be created in the following order. The points are
 * represented by numbers and the faces are preceded by 'f'.
 *
 *                                   2----3
 *       0---------------1           | f0 |
 *       |\      f0      |\          |    |
 *       | \             | \    2----0----1----3     +x=f1
 *       |  2---------------3   | f2 | f3 | f1 |     -x=f2
 *       |  |   f3       |  |   |    |    |    |     +y=f0
 * y     |f2|            |  |   6----4----5----7     -y=f4
 * |     |  |     f5     |f1|        | f4 |          +z=f5
 * |     |  |            |  |        |    |          -z=f3
 * O--x  4--|------------5  |        6----7
 *  \     \ |     f4      \ |        | f5 |
 *   z     \|              \|        |    |
 *          6---------------7        2----3
 */
void Menger::buildCube(vec3 cube, float radius) {
  vec4* verts = new vec4[8];
  int index = 0;
  for(int y=1; y>=-1; y-=2) {
    for(int z=-1; z<=1; z+=2) {
      for(int x=-1; x<=1; x+=2) {
        verts[index++] = vec4(cube + (vec3(x,y,z) * radius), 1.);
      }
    }
  }

  vec4* face = new vec4[4];

  face[0]=verts[2]; face[1]=verts[3]; face[2]=verts[1]; face[3] = verts[0];
  buildFace(face, 0);

  face[0]=verts[1]; face[1]=verts[3]; face[2]=verts[7]; face[3] = verts[5];
  buildFace(face, 1);

  face[0]=verts[2]; face[1]=verts[0]; face[2]=verts[4]; face[3] = verts[6];
  buildFace(face, 2);

  face[0]=verts[0]; face[1]=verts[1]; face[2]=verts[5]; face[3] = verts[4];
  buildFace(face, 3);

  face[0]=verts[4]; face[1]=verts[5]; face[2]=verts[7]; face[3] = verts[6];
  buildFace(face, 4);

  face[0]=verts[6]; face[1]=verts[7]; face[2]=verts[3]; face[3] = verts[2];
  buildFace(face, 5);

  delete[] face;
  delete[] verts;
}
//}}}
//{{{ subdivide functions
/**
 * Subdivide a cube via Menger Sponge.
 *
 * vec4  c      - the center point of the cube to subdivide
 * float radius - The distance from the center to a corner of the cube
 * int   subs   - the number of subdivisions left 
 *
 * This works by assuming that there are 26 other cube centerpoints around
 * `cube`. These are defined to be every combination of + and - of x, y, and
 * z except center (which is already defined). All center cubes along the
 * sides are also ignored (but not center cubes which are edges). The end
 * result of 20 new squares is visualized below where the center square is
 * on lowest z level:
 *
 *             c12--c15--c17
 *              |         |
 *             c08       c10
 *              |         |
 *   c12--c08--c00--c03--c05--c10--c17          y
 *    |         |         |         |           |
 *   c13       c01       c06       c18          |
 *    |         |         |         |           z---x
 *   c14--c09--c02--c04--c07--c11--c19
 *              |         |
 *             c09       c11
 *              |         |
 *             c12--c16--c19
 *              |         |
 *             c13       c18
 *              |         |
 *             c14--c15--c17
 */
void Menger::subdivideMenger(vec3 cube, float radius, int subs) {
  float subLength = 2./3.;
  if(subs > 0) {
    for(int y=-1; y<=1; y++) {
      for(int x=-1; x<=1; x++) {
        for(int z=-1; z<=1; z++) {
          if(y != 0) { // do upper and lower round of cubes
            if(x != 0 || z != 0) { // ignore center cube
              subdivideMenger(cube + vec3(x,y,z) * radius * subLength,
                  radius / 3.0,
                  subs - 1);
            }
          } else { // do middle layer
            if(x != 0 && z!= 0) { // ignore any middle cubes
              subdivideMenger(cube + vec3(x,y,z) * radius * subLength,
                  radius / 3.0,
                  subs - 1);
            }
          }
        }
      }
    }
  } else {
    buildCube(cube, radius);
  }
}

void Menger::subdivideInverseMenger(vec3 cube, float radius, int subs) {
  float subLength = 2./3.;
  if(subs > 0) {
    for(int y=-1; y<=1; y++) {
      for(int x=-1; x<=1; x++) {
        for(int z=-1; z<=1; z++) {
          if(y != 0) { // do upper and lower round of cubes
            if(x != 0 || z != 0) { // don't subdivide center cube
              subdivideInverseMenger(
                  cube + vec3(x,y,z) * radius * subLength,
                  radius / 3.0,
                  subs - 1);
            } else {
              buildCube(cube + vec3(x,y,z) * radius * subLength,
                  radius/3.0);
            }
          } else { // do middle layer
            if(x != 0 && z!= 0) { // don't subdivide middle cubes
              subdivideInverseMenger(
                  cube + vec3(x,y,z) * radius * subLength,
                  radius / 3.0,
                  subs - 1);
            } else {
              buildCube(cube + vec3(x,y,z) * radius * subLength,
                  radius/3.0);
            }
          }
        }
      }
    }
  }
}
//}}}
//{{{ set functions
void Menger::setCenter(vec3 newCenter) {
  cubeCenter = newCenter;
  rebuild();
}

void Menger::setRadius(float newRadius) {
  cubeRadius = newRadius;
  rebuild();
}

void Menger::setSubdivisions(int newSubdivisions) {
  //ensure bounds
  if(newSubdivisions < 0) {
    curSubdivisions = 0;
  } else if(newSubdivisions > maxSubdivisions) {
    curSubdivisions = maxSubdivisions;
  } else {
    curSubdivisions = newSubdivisions;
  }
  rebuild();
}

void Menger::setType(MengerType type) {
  /*if(type == curType) {
    return;
  }*/

  curType = type;
  if(type == NORMAL) {
    computeVerticiesFn = &Menger::computeVerticies;
    subdivideFn = &Menger::subdivideMenger;
    rebuild();
  } else if(type == INVERSE) {
    computeVerticiesFn = &Menger::computeInverseVerticies;
    subdivideFn = &Menger::subdivideInverseMenger;
    rebuild();
  }
}
//}}}
//{{{ in/decrement functions
void Menger::incrementSubdivisions() {
  setSubdivisions(curSubdivisions+1);
}

void Menger::decrementSubdivisions() {
  setSubdivisions(curSubdivisions-1);
}
//}}}
//{{{ build functions
void Menger::rebuild() {
  index = 0;
  vertexCount = (*this.*computeVerticiesFn)(curSubdivisions);

  points = new vec4[vertexCount];
  colors = new vec4[vertexCount];

  (*this.*subdivideFn)(cubeCenter, cubeRadius, curSubdivisions);

  int bufferLen = vertexCount * sizeof(vec4);
  //points
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, bufferLen, points, GL_STATIC_DRAW);
  glError("bound points");
  //colors
  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER, bufferLen, colors, GL_STATIC_DRAW);
  glError("bound colors");

  delete[] points;
  delete[] colors;
}

void Menger::buildModel() {
  rebuild();
  glError("finished rebuild\n");

  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  vPosition = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glError("bound position");

  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  vColor = glGetAttribLocation(program, "vColor");
  glEnableVertexAttribArray(vColor);
  glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glError("bound color");
}
//}}}
