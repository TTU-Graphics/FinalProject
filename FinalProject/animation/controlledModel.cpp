#include "controlledModel.h"
#include <cmath>

int ControlledModel::xSteps = 0;
int ControlledModel::ySteps = 0;
int ControlledModel::zSteps = 0;

ControlledModel::ControlledModel(Model *m, float s, float x, float y, float z) {
 model = m;
 speed = s;
 xLimit = x;
 yLimit = y;
 zLimit = z;
 xDisplacement = 0;
 yDisplacement = 0;
 zDisplacement = 0;

 step(0.0);
}

void ControlledModel::step(float seconds) {
  float x=0,y=0,z=0;
//  std::cout<<ControlledModel::xSteps<<"\t"<<ControlledModel::zSteps<<std::endl;
//  std::cout<<xLimit<<"\t"<<zLimit<<std::endl;;
//  std::cout<<xDisplacement<<"\t"<<zDisplacement<<std::endl<<std::endl;;
  if( abs(xDisplacement) <= xLimit )
  {
	  x = speed*ControlledModel::xSteps;
	  xDisplacement += x;
  }
  if( abs(yDisplacement) <= yLimit )
  {	  
	  y = speed*ControlledModel::ySteps;
	  yDisplacement += y;
  }
  if( abs(zDisplacement) <= zLimit )
  {
	  z = speed*ControlledModel::zSteps;
	  zDisplacement += z;
  }

 
  model->setModelView( model->getModelView() * Translate(x,y,z) );
  ControlledModel::xSteps = 0;
  ControlledModel::ySteps = 0;
  ControlledModel::zSteps = 0;

}