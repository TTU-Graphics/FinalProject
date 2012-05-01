#include "group.h"

Group::Group() {
  transform = mat(1);
}

//{{{ get functions
mat4 Group::getTransform() {
  return transform;
}
//}}}
//{{{ set functions
void Group::setTransform(mat4 transform) {
  this->transform = transform;
}
//}}}
