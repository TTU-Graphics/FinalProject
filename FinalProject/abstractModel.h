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
};

#endif
