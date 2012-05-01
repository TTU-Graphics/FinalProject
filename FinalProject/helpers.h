#ifndef __HELPERS_H
#define __HELPERS_H

#include "Angel.h"
#include <stdio.h>
#include <stdarg.h>

#define PI 3.14159265
#define degToRad (2*PI)/360.
#define pxToRad (2*PI/360)/5.;  // 10px for ever degree angle

//#define DEBUG

int hexCharToInt(char hex);
int hexToInt(const char* hex);
vec3 hexToVec3(const char* hex);
vec4 hexToVec4(const char* hex, float alpha);
vec3 randomColor();
vec4 randomColor4();
vec4 sphericalToPoint(float radius, float theta, float phi, float other);
vec4 pointToSpherical(vec4 point);
vec4 sphericalToPoint(vec4 spherical);
void glError();
void glError(const char* msg);
void glError(const char* name, const char* msg);
void printMat(const char* label, mat4 mat);
void printVec(const char* label, vec3 v);
void printVec(const char* label, vec4 v);
void buildLightShader(const char* curName, const char* newName, int nLights);
char* buildString(const char*, ...);

#endif
