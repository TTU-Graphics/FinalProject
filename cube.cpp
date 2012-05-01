#include "cube.h"

Cube::Cube() {
  vShader = "color.vert";
  fShader = "color.frag";
  name = "Cube";
  vertexCount = 6*2*3;
  bufferCount = 2;
}

void Cube::buildModel() {
  
}
