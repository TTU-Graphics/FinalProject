#ifndef __CONTROLLEDMODEL_H__
#define __CONTROLLEDMODEL_H__

#include "../Angel.h"
#include "../helpers.h"
#include "animation.h"
#include "../model.h"

class ControlledModel: public Animation {
  public:
    static int xSteps;
	static int ySteps;
	static int zSteps;

    ControlledModel(Model *m, float s, float x, float y, float z);

    //overloaded functions
    void step(float seconds);
  private:
    float speed;
	float xLimit, yLimit, zLimit;
	float xDisplacement, yDisplacement, zDisplacement;
    Model *model;
};

#endif
