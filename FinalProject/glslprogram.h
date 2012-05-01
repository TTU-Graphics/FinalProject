#ifndef _GLSLPROGRAM_H
#define _GLSLPROGRAM_H

#include "Angel.h"
#include <stdarg.h>
#include "helpers.h"
#include "SOIL.h"

class GLSLProgram {
  public:
    //constructor
    GLSLProgram(const char*, const char*, const char* name = "GLSLProgram");

    //functions
    void setUniform(mat4, const char*, ...);
    void setUniform(mat3, const char*, ...);
    void setUniform(vec3, const char*, ...);
    void setUniform(vec4, const char*, ...);
    GLuint getProgram();
    void setBuffer(GLuint, GLvoid*, GLenum, int, vec4*, const char*, ...);
    void setBuffer(GLuint, GLvoid*, GLenum, int, vec3*, const char*, ...);
    void setBuffer(GLuint, GLvoid*, GLenum, int, vec2*, const char*, ...);
    void setTexture(const char*, GLenum, int, const char*, ...);
    void getUniform(GLfloat*, const char*, ...);
    void getUniform(GLint*, const char*, ...);
    //GLint getLoc(const char*, ...);

  private:
    GLuint program;
    char* buffer;
    const char* name;

    //functions
    GLint getUnifLoc();
    GLint getAttribLoc();
};

#endif
