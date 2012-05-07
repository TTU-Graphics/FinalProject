#ifndef __INSTANCEMODEL_H
#define __INSTANCEMODEL_H

#include "abstractModel.h"
#include "Angel.h"
#include "model.h"

class InstanceModel: public AbstractModel {
  public:
    //constructor
    InstanceModel(Model*);

    //virtual functions
    virtual void render();
    virtual void setModelView(mat4);
    virtual void setWorldMatrix(mat4);
    virtual void setProjection(mat4);
    virtual mat4 getModelView();
    virtual mat4 getProjection();
    virtual mat4 getWorldMatrix();

  private:
    //variables
    Model* instance;
    mat4 modelView, worldMatrix, projection;
};

#endif
