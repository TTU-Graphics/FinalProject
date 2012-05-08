#ifndef __PARTICLESMODEL_H__
#define __PARTICLESMODEL_H__

#include "../Angel.h"
#include "../helpers.h"
#include "animation.h"
#include "../model.h"
#include "../particles.h"

class ParticlesModel: public Animation {
  public:
    ParticlesModel(Particles *m);

    //overloaded functions
    void step(float seconds);

  private:
    Particles *model;
};

#endif
