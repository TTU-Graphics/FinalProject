#ifndef __ANIMATOR_H
#define __ANIMATOR_H

#include "animation.h"
#include <vector>

class Animator {
  public:
    void addAnimation(Animation*);
    void step(float seconds);
  private:
    std::vector<Animation*> animations;
};

#endif
