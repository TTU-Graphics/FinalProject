#ifndef __SCENE_H
#define __SCENE_H

#include "groupNode.h"
//models
#include "../model.h"
#include "../menger.h"
#include "../shadedModel.h"
#include "../sphere.h"
#include "../texTri.h"
#include "../objModel.h"
#include "../Tesseract.h"
//animation
#include "../animation/animation.h"
#include "../animation/orbitalModel.h"
#include "../animation/oscillatingModel.h"
#include "../animation/controlledModel.h"
//light
#include "../light.h"

#include "../json/json.h"
#include "../helpers.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Scene {
  public:
    //constructor
    Scene(const char*);

    //funtions
    void tick(float);
    void setWorldMatrix(mat4);
    void setProjection(mat4);
    void render();
    void mouseDragged(int,int);
    void setAspect(float);

  private:
    //variables
    vector<Model*> models;
    map<string, Model*> idModels;
    vector<Light*> lights;
    vector<Animation*> animations;
    map<string, void*> nodes;

    //camera variables
    GLfloat fovy;    // Field of view in y angle (degres)
    GLfloat aspect;  // Viewport aspect ratio
    GLfloat zNear, zFar;
    float camTheta, camPhi, upTheta, upPhi;
    float camRadius;
    vec4 eye, at, up;

    //functions
    void buildScene(Json::Value);
    void buildAnimation(Json::Value);
    void buildLight(Json::Value);
    void buildNode(Json::Value);
    void buildCamera(Json::Value);
    Model* buildModel(Json::Value);
    GroupNode* buildGroup(Json::Value);
    void recalculateCamera();
    mat4 getView();

    //get from json functions
    vec3 getVec3(Json::Value);
    vec4 getVec4(Json::Value);
    vec2 getVec2(Json::Value);
    mat4 getMat4(Json::Value);
    mat3 getMat3(Json::Value);
};

#endif
