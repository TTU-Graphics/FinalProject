#include "shadedTri.h"

ShadedTri::ShadedTri() {
  vShader = (char*)"singleLight.vert";
  fShader = (char*)"singleLight.frag";
  name = "ShadedTri";

  vertexCount = 3;
  bufferCount = 2;
  materialAmbient = vec4(1,0,1,1);
  materialDiffuse = vec4(1,0.8,1,1);
  materialSpecular = vec4(1,0,1,1);
  materialShininess = 5.0;
  init();
}

void ShadedTri::buildModel() {
  ambProd = glGetUniformLocation(program, "AmbientProduct");
  difProd = glGetUniformLocation(program, "DiffuseProduct");
  specProd = glGetUniformLocation(program, "SpecularProduct");
  lightPos = glGetUniformLocation(program, "LightPosition");
  matShine = glGetUniformLocation(program, "Shininess");

  glUniform1f(matShine, materialShininess);

  vec4* points = new vec4[vertexCount];
  vec3* normals = new vec3[vertexCount];
  
  vec4 v1 = vec4(-.3, -.3, 0.0, 1.);
  vec4 v2 = vec4( 0.,  .3, 0.0, 1.);
  vec4 v3 = vec4( .3, -.3, 0.0, 1.);
  buildTri(points,0,v1,v2,v3);
  vec3 normal = normalize(cross(v2-v1, v3-v2));
  printVec("ShadedTri Normal",normal);

  for(int i=0;i<vertexCount;i++)
    normals[i] = normal;

  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER,vertexCount*sizeof(vec4),points,GL_STATIC_DRAW);
  vPosition = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glError(name,"vPosition");

  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER,vertexCount*sizeof(vec3),normals,GL_STATIC_DRAW);
  vNormal = glGetAttribLocation(program, "vNormal");
  glEnableVertexAttribArray(vNormal);
  glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glError(name,"vNormal");

  delete[] points;
  delete[] normals;
}

void ShadedTri::setLight(Light* light) {
  glUseProgram(program);
  glError("proding");
  vec4 ambProduct = light->getAmbient() * materialAmbient;
  printVec("ambProd before",ambProduct);
  vec4 difProduct = light->getDiffuse() * materialDiffuse;
  printVec("difProd before",difProduct);
  vec4 specProduct = light->getSpecular() * materialSpecular;
  printVec("specProd before", specProduct);

  glUniform4fv(ambProd, 1, ambProduct);
  glUniform4fv(difProd, 1, difProduct);
  glUniform4fv(specProd, 1, specProduct);
  glUniform4fv(lightPos, 1, light->getPosition());

  vec4 v;
  glGetUniformfv(program,ambProd,v);
  printVec("ambProd",v);
  glGetUniformfv(program,difProd,v);
  printVec("difProd",v);
  glGetUniformfv(program,specProd,v);
  printVec("specProd",v);
  glGetUniformfv(program,lightPos,v);
  printVec("lightPos",v);
}
