#ifndef __ORBITALMODEL_H
#define __ORBITALMODEL_H

#include "../Angel.h"
#include "../helpers.h"
#include "animation.h"
#include "../model.h"

class OrbitalModel: public Animation {
  public:
    OrbitalModel(Model *center, Model *orbiter, float radius, float theta, float phi);

    //overloaded functions
    void step(float seconds);
  private:
    float rotTheta, rotPhi;  //rotation in degrees per second
    float radius;
    Model *centerModel, *orbiterModel;
};

#endif
