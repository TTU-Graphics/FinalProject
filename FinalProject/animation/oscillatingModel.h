#ifndef __OSCILLATINGMODEL_H__
#define __OSCILLATINGMODEL_H__

#include "../Angel.h"
#include "../helpers.h"
#include "animation.h"
#include "../model.h"

class OscillatingModel: public Animation {
  public:
    OscillatingModel(Model *m, float xM, float yM, float zM, float xR, float yR, float zR,
								float x0, float y0, float z0);

    //overloaded functions
    void step(float seconds);
  private:
    float xMax, yMax, zMax; //maximum displacement
    float xRate, yRate, zRate;  //translation speed
	float xDisplacement, yDisplacement, zDisplacement;
    Model *model;
};

#endif
