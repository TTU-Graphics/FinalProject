#ifndef __SPHERE_H
#define __SPHERE_H

#include "shadedModel.h"
#include "helpers.h"
#include "Angel.h"
#include "light.h"

class Sphere: public ShadedModel {
  public:
    Sphere(float radius, int subdivs, int numLights,
        vec4 ambient = vec4(1,0,1,1),
        vec4 diffuse = vec4(1,.8,0,1),
        vec4 specular = vec4(1,0,1,1));

    //functions
    void buildModel();
    //void setLight(Light* light);
    void setModelView(mat4);
    //void setWorldMatrix(mat4);
    
  private:
    //shader variables
    GLuint vPosition, vNormal;
    GLuint ambientProduct, diffuseProduct, specularProduct,
           lightPosition, lightShininess, worldPosition,
           worldRotation, normalMatrix;
    //Light* light;
    //bool hasLight;

    //variables
    //vec4 materialAmbient, materialDiffuse, materialSpecular;
    float radius;
    mat4 scale;
    int subdivisions, ptsIndex;
    vec4* colOptions;
    
    //functions
    void subdivideTri(int subdivs, vec4 p1, vec4 p2, vec4 p4,
        vec4* points, vec4* colors);
    int calculateVerticies(int subdivs);
    vec4 unit(const vec4 &p);
};

#endif
