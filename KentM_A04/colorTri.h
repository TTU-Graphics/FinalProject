#ifndef __TRI_H
#define __TRI_H

#include "model.h"
#include "Angel.h"

//class ChainedTri: public ChainedRotationalModel {
class ChainedTri: public Model {
  public:
    ChainedTri();
    void buildModel();
  private:
    GLuint vPosition, vColor;
};

#endif
