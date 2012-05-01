#ifndef _TEXTUREDMODEL_H
#define _TEXTUREDMODEL_H

#include "Angel.h"
#include "SOIL.h"

class TexturedModel: public Model {
  public:
    char* loadImage(const char* file);
};

#endif
