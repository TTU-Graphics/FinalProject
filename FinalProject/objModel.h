#ifndef __OBJMODEL_H
#define __OBJMODEL_H

#include "shadedModel.h"
#include "Angel.h"
#include "model.h"
#include <vector>
#include <stdio.h>

using namespace std;

class ObjModel: public ShadedModel {
  public:
    ObjModel(const char* objFile, int numLights,
        vec4 ambient = vec4(1,0,1,1),
        vec4 diffuse = vec4(1,.8,0,1),
        vec4 specular = vec4(1,0,1,1));

    // overloaded methods
    void buildModel();
    void preRender();

  private:
    vector<vec4> colVerts, verts;
    vector<vec2> colTex, tex;
    vector<vec3> colNorms, norms;
	vector<vec3> tans;
	vector<vec3> bitans;
    char* textureFile;
    const char* objFileName;
    GLuint glTex;
};

#endif
