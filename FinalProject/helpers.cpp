#include "helpers.h"


/**
 * Converts 1 character hex to int
 * 
 * precondition: cHex element of [0-9A-Ea-e]
 */
int hexCharToInt(char hex) {
  int sub = 48;
  if(hex >= 'A') {
    sub = 55;
  }
  if(hex >= 'a') {
    sub = 87;
  }
  return hex-sub;
}

/**
 * Converts 2 character hex codes to a float from [0,1]
 */
int hexToInt(const char* hex) {
  return hexCharToInt(hex[0])*16 + hexCharToInt(hex[1]);
}

/**
 * Converts 6 character hex codes to vec3
 */
vec3 hexToVec3(const char* hex) {
  return vec3(
      ((float)hexToInt(hex))/256.0,
      ((float)hexToInt(hex+2))/256.0,
      ((float)hexToInt(hex+4))/256.0);
}

vec4 hexToVec4(const char* hex, float alpha) {
  return vec4(
      ((float)hexToInt(hex))/256.0,
      ((float)hexToInt(hex+2))/256.0,
      ((float)hexToInt(hex+4))/256.0,
      alpha);
}

vec3 randomColor() {
  return vec3(
      (float)rand()/(float)RAND_MAX,
      (float)rand()/(float)RAND_MAX,
      (float)rand()/(float)RAND_MAX);
}

vec4 randomColor4() {
  return vec4(
      (float)rand()/(float)RAND_MAX,
      (float)rand()/(float)RAND_MAX,
      (float)rand()/(float)RAND_MAX,
      1.);
}

/**
 * spherical(1,0,0) = cartesian(0,0,1)
 * theta = [-PI/2, PI/2]
 * phi   = [-PI,   PI  ]
 */
vec4 sphericalToPoint(float radius, float theta, float phi, float other) {
  theta -= PI*.5;
  phi   += PI;
  return vec4(
      radius * sin(theta) * sin(phi),
      radius * cos(theta),
      radius * sin(theta) * cos(phi),
      other);
}

/**
 * returns a vec4 representing:
 *   x = radius
 *   y = theta
 *   z = phi
 *   w = 1.0
 */
vec4 pointToSpherical(vec4 point) {
  float radius = sqrt(pow(point.x,2) + pow(point.y,2) + pow(point.z,2));
  float theta = PI/2, phi = 0;
  if((point.x < -0.00001 || point.x > 0.00001) &&
     (point.z < -0.00001 || point.z > 0.00001)) {
    theta = acos(point.y/radius);
    phi = atan(point.x/point.z);
  } else if(point.y < 0.0) {
    theta = -PI/2;
  }
  return vec4(radius,theta,phi,1.0);
}

vec4 sphericalToPoint(vec4 spherical) {
  return sphericalToPoint(spherical.x, spherical.y, spherical.z,
      spherical.w);
}

/**
 * prints an OpenGL error if there is one.
 */
void glError() {
  GLenum err = glGetError();
  switch(err) {
    case GL_NO_ERROR:
      break;
    case GL_INVALID_ENUM:
      printf("gl error - invalid enum\n");
      break;
    case GL_INVALID_VALUE:
      printf("gl error - invalid value\n");
      break;
    case GL_INVALID_OPERATION:
      printf("gl error - invalid operation\n");
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      printf("gl error - invalid framebuffer operation\n");
      break;
    case GL_OUT_OF_MEMORY:
      printf("gl error - out of memory\n");
      break;
  }
}

void glError(const char* msg) {
  GLenum err = glGetError();
  switch(err) {
    case GL_NO_ERROR:
      break;
    case GL_INVALID_ENUM:
      printf("%s\n\tgl error - invalid enum\n",msg);
      break;
    case GL_INVALID_VALUE:
      printf("%s\n\tgl error - invalid value\n",msg);
      break;
    case GL_INVALID_OPERATION:
      printf("%s\n\tgl error - invalid operation\n",msg);
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      printf("%s\n\tgl error - invalid framebuffer operation\n",msg);
      break;
    case GL_OUT_OF_MEMORY:
      printf("%s\n\tgl error - out of memory\n",msg);
      break;
  }
}

void glError(const char* name, const char* msg) {
  GLenum err = glGetError();
  switch(err) {
    case GL_NO_ERROR:
      break;
    case GL_INVALID_ENUM:
      printf("%s: %s\n\tgl error - invalid enum\n",name,msg);
      break;
    case GL_INVALID_VALUE:
      printf("%s: %s\n\tgl error - invalid value\n",name,msg);
      break;
    case GL_INVALID_OPERATION:
      printf("%s: %s\n\tgl error - invalid operation\n",name,msg);
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      printf("%s: %s\n\tgl error - invalid framebuffer operation\n",name,msg);
      break;
    case GL_OUT_OF_MEMORY:
      printf("%s: %s\n\tgl error - out of memory\n",name,msg);
      break;
  }
}

void printMat(const char* label, mat4 mat) {
  printf("%s = [%f, %f, %f, %f\n", label, mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
  printf("\t%f, %f, %f, %f\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
  printf("\t%f, %f, %f, %f\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
  printf("\t%f, %f, %f, %f\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
}

void printVec(const char* label, vec3 v) {
  printf("%s(%f, %f, %f)\n",label,v.x,v.y,v.z);
}

void printVec(const char* label, vec4 v) {
  printf("%s(%f, %f, %f, %f)\n",label,v.x,v.y,v.z,v.w);
}

void buildLightShader(const char* curName, const char* newName, int nLights) {
  char* buffer = new char[512];
  FILE *in, *out;
  int bytes, count = 0;

  sprintf(buffer, "%s.vert", curName);
  in = fopen(buffer, "r");
  sprintf(buffer, "%s.vert", newName);
  out = fopen(buffer, "w");
  fprintf(out,"const int nLights = %d;\n",nLights);
  while(true) {
    bytes = fread(buffer, 1, 512, in);
    fwrite(buffer, 1, bytes, out);
    if(bytes < 512) {
      break;
    }
    if(count++ > 50) {
      printf("shader file \"%s.vert\" is more than 50*512 bytes, modify helpers.cpp if you wish to increase this limit.\n",curName);
      break;
    }
  }
  
  fclose(in);
  fclose(out);

  count = 0;
  sprintf(buffer, "%s.frag", curName);
  in = fopen(buffer, "r");
  sprintf(buffer, "%s.frag", newName);
  out = fopen(buffer, "w");
  fprintf(out,"const int nLights = %d;\n",nLights);
  while(true) {
    bytes = fread(buffer, 1, 512, in);
    fwrite(buffer, 1, bytes, out);
    if(bytes < 512) {
      break;
    }
    if(count++ > 50) {
      printf("shader file \"%s.vert\" is more than 50*512 bytes, modify helpers.cpp if you wish to increase this limit.\n",curName);
      break;
    }
  }

  fclose(in);
  fclose(out);
}

char* buildString(const char* format, ...) {
  va_list args;
  va_start(args,format);
  char* buffer = new char[256];
  vsprintf(buffer, format, args);
  va_end(args);
  return buffer;
}
