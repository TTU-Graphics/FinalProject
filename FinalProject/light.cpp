#include "light.h"

Light::Light(vec4 position, vec4 ambient, vec4 diffuse, vec4 specular,
			 vec4 direction, GLfloat angle) {
  this->position = position;
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
  this->direction = direction;
  this->angle = angle*DegreesToRadians;
}

//{{{ set functions
void Light::setPosition(vec4 position) {
  this->position = position;
}

void Light::setAmbient(vec4 ambient) {
  this->ambient = ambient;
}

void Light::setDiffuse(vec4 diffuse) {
  this->diffuse = diffuse;
}

void Light::setSpecular(vec4 specular) {
  this->specular = specular;
}

void Light::setDirection(vec4 direction) {
  this->direction = direction;
}

void Light::setAngle(GLfloat angle) {
  this->angle = angle;
}

/*void Light::setWorldMatrix(mat4 mat) {
  this->worldMatrix = mat;
}*/
//}}}
//{{{ get functions
vec4 Light::getPosition() {
  //return worldMatrix*position;
  return position;
}

vec4 Light::getAmbient() {
  return ambient;
}

vec4 Light::getDiffuse() {
  return diffuse;
}

vec4 Light::getSpecular() {
  return specular;
}

vec4 Light::getDirection() {
  return direction;
}

GLfloat Light::getAngle() {
  return angle;
}
//}}}
