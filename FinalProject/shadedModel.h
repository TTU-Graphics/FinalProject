#ifndef _SHADEDMODEL_H
#define _SHADEDMODEL_H

#include "Angel.h"
#include "model.h"
#include "light.h"
#include "helpers.h"
#include <vector>

class ShadedModel: public Model {
  public:
    ShadedModel(int numLights,vec4,vec4,vec4);
    void setWorldMatrix(mat4);
    void setLight(Light*,int);

  protected:
    GLuint ambientProduct, diffuseProduct, specularProduct,
           lightPosition, lightShininess, worldPosition,
           worldRotation, normalMatrix;
    std::vector<Light*> lights;
    vec4 materialAmbient, materialDiffuse, materialSpecular;
    bool hasAllLights;
    
    void updateLightPositions();
    //void updateMaterialProducts();
};

#endif
