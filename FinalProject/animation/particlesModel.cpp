#include "particlesModel.h"
#include <cmath>

ParticlesModel::ParticlesModel(Particles *m) {
  model = m;
  step(0.0);
}

void ParticlesModel::step(float seconds) {
  model->step(seconds);
}
