#include "sphere.h"

Sphere::Sphere(float radius, int subdivs,
    int numLights, vec4 ambient, vec4 diffuse,
    vec4 specular): ShadedModel(numLights, ambient, diffuse, specular) {
  this->radius = radius;
  subdivisions = subdivs;

  name = "sphere";
  buildLightShader("multLight",buildString("multLight-%d",numLights),numLights);
  vShader = buildString("multLight-%d.vert",numLights);
  fShader = buildString("multLight-%d.frag",numLights);
  //vShader = "multlight.vert";
  //fShader = "multlight.frag";
  vertexCount = calculateVerticies(subdivisions);
  bufferCount = 2;

  /*materialAmbient = vec4(1,0,1,1);
  materialDiffuse = vec4(1,.8,0,1);
  materialSpecular = vec4(1,0,1,1);*/

  //hasLight = false;

  printf("sphere before init\n");
  init();
  printf("sphere after init\n");
}

//{{{ build model functions
void Sphere::buildModel() {
  printf("building sphere\n");
  glUseProgram(program);
  vec4* points = new vec4[vertexCount];
  vec4* normals = new vec4[vertexCount];
  ptsIndex = 0;

  colOptions = new vec4[3];
  colOptions[0] = vec4(1,0,0,1);
  colOptions[1] = vec4(0,1,0,1);
  colOptions[2] = vec4(0,0,1,1);
  
  scale = mat4(1) * radius;
  scale[3][3] = 1.;
  vec4* tetra = new vec4[4];
  tetra[0] = vec4(0.0, 0.0, 1.0, 1.0);
  tetra[1] = vec4(0.0, 0.942809, -0.333333, 1.0);
  tetra[2] = vec4(-0.816497, -0.471405, -0.333333, 1.0);
  tetra[3] = vec4(0.816497, -0.471405, -0.333333, 1.0);

  subdivideTri(subdivisions, tetra[0], tetra[1], tetra[2], points, normals);
  subdivideTri(subdivisions, tetra[3], tetra[2], tetra[1], points, normals);
  subdivideTri(subdivisions, tetra[0], tetra[3], tetra[1], points, normals);
  subdivideTri(subdivisions, tetra[0], tetra[2], tetra[3], points, normals);

  delete[] tetra;

  /*glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER,vertexCount*sizeof(vec4),points,GL_STATIC_DRAW);
  vPosition = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glError(name,"vPosition");*/

  prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,points,"vPosition");

  /*glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER,vertexCount*sizeof(vec4),normals,GL_STATIC_DRAW);
  vNormal = glGetAttribLocation(program, "vNormal");
  glEnableVertexAttribArray(vNormal);
  glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glError(name,"vNormal");*/

  prog->setBuffer(buffers[1],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,normals,"vNormal");

  delete[] points;
  delete[] normals;

  ambientProduct = glGetUniformLocation(program, "AmbientProduct");
  diffuseProduct = glGetUniformLocation(program, "DiffuseProduct");
  specularProduct = glGetUniformLocation(program, "SpecularProduct");
  lightPosition = glGetUniformLocation(program, "LightPosition");

  normalMatrix = glGetUniformLocation(program, "NormalMatrix");
  /*worldPosition = glGetUniformLocation(program, "WorldPosition");
  worldRotation = glGetUniformLocation(program, "WorldRotation");//*/

  // set material shininess
  glUniform1f( glGetUniformLocation(program, "Shininess"), 5.0);

  printf("done building sphere\n");
}

void Sphere::subdivideTri(int subdivs, vec4 p1, vec4 p2, vec4 p3,
    vec4* points, vec4* normals) {
  glUseProgram(program);
  if(subdivs > 0) {
    // from Angle example 5.1
    vec4 v1, v2, v3;
    v1 = unit(p1 + p2);
    v2 = unit(p1 + p3);
    v3 = unit(p2 + p3);   
    subdivideTri(subdivs-1, p1, v1, v2, points, normals);
    subdivideTri(subdivs-1, p3, v2, v3, points, normals);
    subdivideTri(subdivs-1, p2, v3, v1, points, normals);
    subdivideTri(subdivs-1, v1, v3, v2, points, normals);
  } else {
    buildTri(points, ptsIndex,
        scale * p1,
        scale * p2,
        scale * p3);
    vec4 normal = vec4(normalize(cross(p2-p1, p3-p2)),0);
    //printVec("normal",normal);
    for(int i=ptsIndex;i<ptsIndex+3;i++) {
      normals[i] = normal;
    }
    ptsIndex += 3;
  }
}

int Sphere::calculateVerticies(int subdivs) {
  int tris = 4;
  for(int i=0;i<subdivs;i++) {
    tris *= 4;
  }
  return tris*3; //triangles * 3 points per tri
}

void Sphere::setModelView(mat4 mat) {
  /*glUseProgram(program);
  glUniformMatrix4fv(modelView, 1, GL_TRUE, mat);
  glError(name,"setting Model");*/
  prog->setUniform(mat, "ModelView");

  /*mat3 normMat(
      mat[0][0], mat[1][0], mat[2][0],
      mat[0][1], mat[1][1], mat[2][1],
      mat[0][2], mat[1][2], mat[2][2]);
  glUniformMatrix3fv(normalMatrix, 1, GL_TRUE, normMat);//inverse(norm));
  glError(name,"setting normal matrix");*/

  /*if(hasLight) {
    glUniform4fv(lightPosition, 1, light->getPosition());
    glError(name,"setting new light position");
  }*/

  /*mat4 norm(1);
  norm[0][3] = mat[0][3];
  norm[1][3] = mat[1][3];
  norm[2][3] = mat[2][3];
  glUniformMatrix4fv(worldPosition, 1, GL_TRUE, norm);
  glError(name,"setting world position");

  mat[0][3] = 0;
  mat[1][3] = 0;
  mat[2][3] = 0;
  glUniformMatrix4fv(worldRotation, 1, GL_TRUE, mat);
  glError(name,"setting world rotation");*/
}//*/

/*void Sphere::setWorldMatrix(mat4 mat) {
  glUseProgram(program);
  mat3 normMat(
      mat[0][0], mat[1][0], mat[2][0],
      mat[0][1], mat[1][1], mat[2][1],
      mat[0][2], mat[1][2], mat[2][2]);
  glUniformMatrix3fv(normalMatrix, 1, GL_TRUE, normMat);
  glError(name,"setting normal matrix2");
}*/

/*
 * from Angel example 5.1
 */
vec4 Sphere::unit(const vec4 &p)
{
  float len = p.x*p.x + p.y*p.y + p.z*p.z;

  vec4 t;
  if ( len > DivideByZeroTolerance ) {
    t = p / sqrt(len);
    t.w = 1.0;
  }

  return t;
}
//}}}
//{{{ setLight()
/*void Sphere::setLight(Light* light) {
  bindModel();
  this->light = light;
  glUseProgram(program);
  vec4 ambProduct = light->getAmbient() * materialAmbient;
  vec4 difProduct = light->getDiffuse() * materialDiffuse;
  vec4 specProduct = light->getSpecular() * materialSpecular;

  glUniform4fv(diffuseProduct, 1, difProduct);
  glUniform4fv(ambientProduct, 1, ambProduct);
  glUniform4fv(specularProduct, 1, specProduct);
  glUniform4fv(lightPosition, 1, light->getPosition());

  hasLight = true;
  unbindModel();
}*/
//}}}
