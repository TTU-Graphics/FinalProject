#include "model.h"

Model::Model() {
//  init();
}

void Model::init() {
#ifdef __APPLE__
  glGenVertexArraysAPPLE(1, &vao);
  glBindVertexArrayAPPLE(vao);
#else
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
#endif
  prog = new GLSLProgram(vShader, fShader);
  program = prog->getProgram(); //TODO remove this variable and line
  //glUseProgram(program);
  glUseProgram(prog->getProgram());

  buffers = new GLuint[bufferCount];
  glGenBuffers(bufferCount, buffers);

  setModelView(mat4(1));
  setWorldMatrix(mat4(1));
  buildModel();

  /*modelView = glGetUniformLocation(program, "modelView");
  projection = glGetUniformLocation(program, "projection");*/

  //unbindModel();
  glError(name,"finished init");
}

void Model::buildTri(vec4* points, int index, vec4 p1, vec4 p2, vec4 p3) {
  points[index] = p1;
  points[index+1] = p2;
  points[index+2] = p3;
}

void Model::unbindModel() {
#ifdef __APPLE__
  glBindVertexArrayAPPLE(0);
#else
  glBindVertexArray(0);
#endif
}

void Model::bindModel() {
#ifdef __APPLE__
  glBindVertexArrayAPPLE(vao);
#else
  glBindVertexArray(vao);
#endif
  glUseProgram(prog->getProgram());
}

void Model::render() {
  bindModel();
  if(!customRender()) {
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  }
  glError(name,"Model render");
  unbindModel();
}
//{{{ matrix get functions
mat4 Model::getModelView() {
  glUseProgram(prog->getProgram());  //TODO: is this needed??? look at glGetUniformfv()
  mat4 mat(0);
  //glGetUniformfv(program, modelView, mat);
  prog->getUniform(mat, "ModelView");
  return transpose(mat);
}

mat4 Model::getProjection() {
  glUseProgram(program);  //TODO: is this needed??? look at glGetUniformfv()
  mat4 mat(0);
  //glGetUniformfv(program, projection, mat);
  prog->getUniform(mat, "Projection");
  return transpose(mat);
}

mat4 Model::getWorldMatrix() {
  mat4 mat;
  prog->getUniform(mat,"WorldMatrix");
  return transpose(mat);
}

//}}}
//{{{ matrix set functions
/*void Model::setWorldView(mat4 mat) {
  glUniformMatrix4fv(worldView, 1, GL_TRUE, mat);
}*/

void Model::setModelView(mat4 mat) {
  /*glUseProgram(program);
  glUniformMatrix4fv(modelView, 1, GL_TRUE, mat);
  glError(name,"setting Model");*/
  prog->setUniform(mat, "ModelView");
}

void Model::setProjection(mat4 mat) {
  /*glUseProgram(program);
  glUniformMatrix4fv(projection, 1, GL_TRUE, mat);
  glError(name,"setting Projection");*/
  prog->setUniform(mat, "Projection");
}

void Model::setWorldMatrix(mat4 mat) {
  prog->setUniform(mat, "WorldMatrix");
}
//}}}
//{{{ optional functions
bool Model::customRender() {
  return false;
}

void Model::preRender() {
}

void Model::postRender() {
}
//}}}
