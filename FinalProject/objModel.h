#ifndef __OBJMODEL_H
#define __OBJMODEL_H

#include "Angel.h"
#include "model.h"
#include <vector>
#include <stdio.h>

using namespace std;

class ObjModel: public Model {
  public:
    ObjModel(const char*);

    // overloaded methods
    void buildModel();
    void preRender();

  private:
    vector<vec4> colVerts, verts;
    vector<vec2> colTex, tex;
    vector<vec3> colNorms, norms;
    char* textureFile;
    const char* objFileName;
};

#endif
