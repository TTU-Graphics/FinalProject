#ifndef __ABSTRACTMODEL_H
#define __ABSTRACTMODEL_H

#include "Angel.h"

class AbstractModel {
  public:
    //functions
    virtual void render() =0;
    virtual void setModelView(mat4) =0;
    virtual void setWorldMatrix(mat4) =0;
    virtual void setProjection(mat4) =0;
    virtual mat4 getModelView() =0;
    virtual mat4 getProjection() =0;
    virtual mat4 getWorldMatrix() =0;
};

#endif
