#ifndef __LIGHT_H
#define __LIGHT_H

#include "Angel.h"

class Light {
  public:
    Light(vec4 position, vec4 ambient, vec4 diffuse, vec4 specular,
		vec4 direction=(1,1,1,1), GLfloat angle=180.0);

    // set functions
    void setPosition(vec4 position);
    void setAmbient(vec4 ambient);
    void setDiffuse(vec4 diffuse);
    void setSpecular(vec4 specular);
    void setDirection(vec4 direction);
	void setAngle(GLfloat angle);
    //void setWorldMatrix(mat4);
    // get functions
    vec4 getPosition();
    vec4 getAmbient();
    vec4 getDiffuse();
    vec4 getSpecular();
    vec4 getDirection();
    GLfloat getAngle();
  private:
    vec4 position, ambient, diffuse, specular, direction;
	GLfloat angle;
	mat4 worldMatrix;
};

#endif
