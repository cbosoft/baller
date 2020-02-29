#include "simrenderer.hpp"

bool Renderer::frameEnded(const Ogre::FrameEvent &evt)
{
  this->time += evt.timeSinceLastFrame;
  auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
  auto anim = scene_manager->getAnimation("anim");
  anim->apply(this->time);
  std::cerr << this->time << std::endl;
  return true;
}
