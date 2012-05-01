#include "animator.h"

void Animator::addAnimation(Animation* anim) {
  animations.push_back(anim);
}

void Animator::step(float seconds) {
  std::vector<Animation*>::iterator it;
  for(it = animations.begin(); it != animations.end(); it++) {
    (*it)->step(seconds);
  }
}
