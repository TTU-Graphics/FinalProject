#ifndef __SHADEDTRI_H
#define __SHADEDTRI_H

#include "model.h"
#include "Angel.h"
#include "light.h"

//class ChainedTri: public ChainedRotationalModel {
class ShadedTri: public Model {
  public:
    ShadedTri();
    void buildModel();
    void setLight(Light* light);
  private:
    GLuint vPosition, vNormal;
    GLuint ambProd, difProd, specProd, lightPos, matShine;
    vec4 materialAmbient, materialDiffuse, materialSpecular;
    float materialShininess;
};

#endif
