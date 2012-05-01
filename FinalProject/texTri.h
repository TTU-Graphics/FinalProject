#ifndef __TEXTRI_H
#define __TEXTRI_H

#include "model.h"
#include "Angel.h"

//class ChainedTri: public ChainedRotationalModel {
class TexTri: public Model {
  public:
    TexTri(const char*);
    void buildModel();
  private:
    const char* texture;
};

#endif
