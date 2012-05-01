#ifndef __GROUPNODE_H
#define __GROUPNODE_H

#include "../Angel.h"
#include "../model.h"
#include <vector>

using namespace std;

class GroupNode {
  public:
    //constructor
    GroupNode();

    //functions
    void addModel(Model*);

    //get functions
    mat4 getTransform();

    //set functions
    void setTransform(mat4);

  private:
    mat4 transform;
    vector<Model*> models;
};

#endif
