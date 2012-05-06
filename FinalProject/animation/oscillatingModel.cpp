#include "oscillatingModel.h"
#include <cmath>

OscillatingModel::OscillatingModel(Model *m, float xM, float yM, float zM,
								   float xR, float yR, float zR,
								   float x0, float y0, float z0 ) {
 model = m;
 xMax = xM;
 yMax = yM;
 zMax = zM;
 xRate = xR;
 yRate = yR;
 zRate = zR;
 xDisplacement = 0.0;
 yDisplacement = 0.0;
 zDisplacement = 0.0;

 model->setModelView(
     model->getModelView() *
     Translate(x0, y0, z0));

 step(0.0);
}

void OscillatingModel::step(float seconds) {
  if( abs(xDisplacement) >= xMax )
  {
	  xRate = -1.0*xRate;
  }
  if( abs(yDisplacement) >= yMax )
  {
	  yRate = -1.0*yRate;
  }
  if( abs(zDisplacement) >= zMax )
  {
	  zRate = -1.0*zRate;
  }

  xDisplacement += xRate;
  yDisplacement += yRate;
  zDisplacement += zRate;

  model->setModelView(
      model->getModelView() *
      Translate(xRate, yRate, zRate));
}
