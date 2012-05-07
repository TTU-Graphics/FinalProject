#ifndef __MODEL_H
#define __MODEL_H

#include "Angel.h"
#include "helpers.h"
#include "glslprogram.h"
#include "abstractModel.h"

class Model: public AbstractModel {
  public:
    //variables
    char *vShader, *fShader;
    const char *name;
    GLuint* buffers;
    int vertexCount, bufferCount;

    //functions
    Model();
    void bindModel();
    void unbindModel();
    void init();
    void render();
    virtual void setModelView(mat4);
    virtual void setWorldMatrix(mat4);
    virtual void setProjection(mat4);

    //getter functions
    virtual mat4 getModelView();
    virtual mat4 getProjection();
    virtual mat4 getWorldMatrix();

    //optional functions
    virtual bool customRender();
    virtual void preRender();
    virtual void postRender();

    //pure virtual functions
    virtual void buildModel() =0;
  protected:
    GLuint vao, program;//, modelView, projection;
    GLSLProgram* prog;
    void buildTri(vec4* points, int index, vec4 p1, vec4 p2, vec4 p3);
};

#endif
