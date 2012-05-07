//#ifndef __SPHERE_H
//#define __SPHERE_H
//#include "shadedModel.h"
//#include "helpers.h"
//#include "Angel.h"
//#include "light.h"
//
//class Particles: public ShadedModel {
//  public:
//    Particles(float radius, int subdivs, int numLights,
//        vec4 ambient = vec4(1,0,1,1),
//        vec4 diffuse = vec4(1,.8,0,1),
//        vec4 specular = vec4(1,0,1,1));
//
//    //functions
//    void buildModel();
//    void setModelView(mat4);
//
//	bool customRender();
//    
//  private:
//    //shader variables
//    GLuint vPosition, vNormal;
//    GLuint ambientProduct, diffuseProduct, specularProduct,
//           lightPosition, lightShininess, worldPosition,
//           worldRotation, normalMatrix;
//
//    //variables
//    float radius;
//    mat4 scale;
//    int subdivisions, ptsIndex;
//    vec4* colOptions;
//    
//    //functions
//};
//
//#endif
