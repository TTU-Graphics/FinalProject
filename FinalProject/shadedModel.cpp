#include "shadedModel.h"

ShadedModel::ShadedModel(int numLights, vec4 ambient, vec4 diffuse,
    vec4 specular) {
  materialAmbient = ambient;
  materialDiffuse = diffuse;
  materialSpecular = specular;
  lights = *(new std::vector<Light*>(numLights));
  hasAllLights = false;
}

void ShadedModel::setWorldMatrix(mat4 mat) {
  prog->setUniform(mat,"WorldMatrix");
  //update normal matrix
  mat3 normMat(
      mat[0][0], mat[1][0], mat[2][0],
      mat[0][1], mat[1][1], mat[2][1],
      mat[0][2], mat[1][2], mat[2][2]);
  //glUniformMatrix3fv(normalMatrix, 1, GL_TRUE, normMat);
  prog->setUniform(normMat, "NormalMatrix");

  // update lights
  updateLightPositions();
  
  //TODO: need to save?
}

void ShadedModel::setLight(Light* light, int index) {
  if(!hasAllLights && index == lights.size()-1) {
    hasAllLights = true;
  }
  lights[index] = light;
  //TODO set the light properties
  vec4 ambProduct = lights[index]->getAmbient() * materialAmbient;
  vec4 difProduct = lights[index]->getDiffuse() * materialDiffuse;
  vec4 specProduct = lights[index]->getSpecular() * materialSpecular;

  /*glUniform4fv(diffuseProduct, 1, difProduct);
  glUniform4fv(ambientProduct, 1, ambProduct);
  glUniform4fv(specularProduct, 1, specProduct);
  glUniform4fv(lightPosition, 1, light->getPosition());*/
  prog->setUniform(ambProduct, "lights[%d].AmbientProduct", index);
  prog->setUniform(difProduct, "lights[%d].DiffuseProduct", index);
  prog->setUniform(specProduct, "lights[%d].SpecularProduct", index);
  prog->setUniform(light->getPosition(), "lights[%d].Position", index);
  prog->setUniform(light->getDirection(), "lights[%d].Direction", index);
  prog->setUniform(light->getAngle(), "lights[%d].Angle", index);
  updateLightPositions();
}

void ShadedModel::updateLightPositions() {
  if(hasAllLights) {
    mat4 mat = getWorldMatrix();
    std::vector<Light*>::iterator it;
    int index = 0;
    for(it = lights.begin(); it != lights.end(); it++) {
      prog->setUniform(mat * (*it)->getPosition(), "lights[%d].Position",
          index);
      index++;
    }
  }
}
