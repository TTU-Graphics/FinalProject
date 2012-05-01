#include "groupNode.h"

GroupNode::GroupNode() {
  transform = mat4(1);
}

void GroupNode::addModel(Model* m) {
  models.push_back(m);
  m->setModelView(transform * m->getModelView());
}

mat4 GroupNode::getTransform() {
  return transform;
}

void GroupNode::setTransform(mat4 trans) {
  transform = trans;
  vector<Model*>::iterator modelIterator;
  for(modelIterator = models.begin(); modelIterator != models.end(); modelIterator++) {
    (*modelIterator)->setModelView(
        trans * (*modelIterator)->getModelView());
  }
}
