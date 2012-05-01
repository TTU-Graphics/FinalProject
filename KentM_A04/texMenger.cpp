#include "texMenger.h"

TextureMenger::TextureMenger(float radius, int subdivs): Menger(
    vec3(0,0,0), radius, subdivs) {
  
}

void TextureMenger::buildCube(vec3 center, float radius) {
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

void buildFace(vec4* face, FaceType type) {
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
