#include "glslprogram.h"

#define getBuffer() va_list args;\
  va_start(args,format);\
vsprintf(buffer, format, args);\
va_end(args);\
glUseProgram(program);

int GLSLProgram::GTexNum = 0;
GLSLProgram::GLSLProgram(const char* vShader, const char* fShader,
    const char* name) {
  program = InitShader(vShader, fShader);
  buffer = new char[256];
  this->name = name;
}

void GLSLProgram::setUniform(mat4 m, const char* format, ...) {
  getBuffer();
  glUniformMatrix4fv(getUnifLoc(), 1, GL_TRUE, m);
  glError("glslprogram setting uniform mat4");
}

void GLSLProgram::setUniform(mat3 m, const char* format, ...) {
  getBuffer();
  glUniformMatrix3fv(getUnifLoc(), 1, GL_TRUE, m);
}

void GLSLProgram::setUniform(vec3 v, const char* format, ...) {
  getBuffer();
  glUniform3fv(getUnifLoc(), 1, v);
}

void GLSLProgram::setUniform(vec4 v, const char* format, ...) {
  getBuffer();
  glUniform4fv(getUnifLoc(), 1, v);
}

GLuint GLSLProgram::getProgram() {
  return program;
}
// set vec4 buffer
void GLSLProgram::setBuffer(GLuint buf, GLvoid* offset, GLenum type, int arrSize,
    vec4* arr, const char* format, ...) {
  getBuffer();
  glUseProgram(program);
  
  glBindBuffer(GL_ARRAY_BUFFER, buf);
  glBufferData(GL_ARRAY_BUFFER, arrSize*sizeof(vec4), arr, GL_STATIC_DRAW);
  GLuint ptr = getAttribLoc();
  glEnableVertexAttribArray(ptr);
  glVertexAttribPointer(ptr, 4, type, GL_FALSE, 0, offset);
  glError(name,buffer);
}

// set vec3 buffer
void GLSLProgram::setBuffer(GLuint buf, GLvoid* offset, GLenum type, int arrSize,
    vec3* arr, const char* format, ...) {
  getBuffer();
  glUseProgram(program);
  
  glBindBuffer(GL_ARRAY_BUFFER, buf);
  glBufferData(GL_ARRAY_BUFFER, arrSize*sizeof(vec3), arr, GL_STATIC_DRAW);
  GLuint ptr = getAttribLoc();
  glEnableVertexAttribArray(ptr);
  glVertexAttribPointer(ptr, 3, type, GL_FALSE, 0, offset);
  glError(name,buffer);
}

// set vec2 buffer
void GLSLProgram::setBuffer(GLuint buf, GLvoid* offset, GLenum type, int arrSize,
    vec2* arr, const char* format, ...) {
  getBuffer();
  glUseProgram(program);
  
  glBindBuffer(GL_ARRAY_BUFFER, buf);
  glBufferData(GL_ARRAY_BUFFER, arrSize*sizeof(vec2), arr, GL_STATIC_DRAW);
  GLuint ptr = getAttribLoc();
  glEnableVertexAttribArray(ptr);
  glVertexAttribPointer(ptr, 2, type, GL_FALSE, 0, offset);
  glError(name,buffer);
}

void GLSLProgram::getUniform(GLfloat* data, const char* format, ...) {
  getBuffer();
  glGetUniformfv(program, getUnifLoc(), data);
}

void GLSLProgram::getUniform(GLint* data, const char* format, ...) {
  getBuffer();
  glGetUniformiv(program, getUnifLoc(), data);
}

GLint GLSLProgram::getUnifLoc() {
  return glGetUniformLocation(program, buffer);
}

GLint GLSLProgram::getAttribLoc() {
  return glGetAttribLocation(program, buffer);
}

GLuint GLSLProgram::setTexture(const char* imgFile, const char* format, ...) {
  getBuffer();

  texNum = GTexNum;
  GTexNum++;

  activeTex = SOIL_load_OGL_texture(
      imgFile,
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
        SOIL_FLAG_COMPRESS_TO_DXT);
  printf("ActiveTex = %d\n",activeTex);
  printf("texNum = %d\n",texNum);

  glActiveTexture(GL_TEXTURE0 + texNum);
  glBindTexture(GL_TEXTURE_2D, activeTex);
  glUniform1i(glGetUniformLocation(program,buffer), texNum);

  return activeTex;
}

void GLSLProgram::bindTexture() {
  glActiveTexture(GL_TEXTURE0 + texNum);
  glBindTexture(GL_TEXTURE_2D, activeTex);
}
