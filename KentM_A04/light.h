#ifndef __LIGHT_H
#define __LIGHT_H

#include "Angel.h"

class Light {
  public:
    Light(vec4 position, vec4 ambient, vec4 diffuse, vec4 specular);

    // set functions
    void setPosition(vec4 position);
    void setAmbient(vec4 ambient);
    void setDiffuse(vec4 diffuse);
    void setSpecular(vec4 specular);
    //void setWorldMatrix(mat4);
    // get functions
    vec4 getPosition();
    vec4 getAmbient();
    vec4 getDiffuse();
    vec4 getSpecular();
  private:
    vec4 position, ambient, diffuse, specular;
    mat4 worldMatrix;
};

#endif
