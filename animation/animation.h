#ifndef __ANIMATION_H
#define __ANIMATION_H

class Animation {
  public:
    virtual void step(float seconds) =0;
};

#endif
