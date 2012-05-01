#ifndef __TEXMENGER_H
#define __TEXMENGER_H

#include "menger.h"
#include "Angel.h"

class TexturedMenger: public Menger {
  public:
    TexturedMenger(float radius, int subdivs);
  protected:
    void buildFace(vec4* face, FaceType type);
    void buildCube(vec3 center, float radius);

  private:
    enum FaceType { XP, XN, YP, YN, ZP, ZN};
}

#endif
