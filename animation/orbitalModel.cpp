#include "orbitalModel.h"

OrbitalModel::OrbitalModel(Model* center, Model* orbiter, float radius,
    float theta, float phi) {
 centerModel = center;
 orbiterModel = orbiter;
 rotTheta = theta * degToRad;
 rotPhi = phi * degToRad;
 this->radius = radius;
 step(0.0);
}

void OrbitalModel::step(float seconds) {
  vec4 v = sphericalToPoint(radius, rotTheta * seconds, rotPhi * seconds,
      1.0);
  orbiterModel->setModelView(
      centerModel->getModelView() *
      Translate(v));
}
