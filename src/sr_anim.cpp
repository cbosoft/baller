#include "simrenderer.hpp"
double Renderer::add_fps_get_av(double fps)
{
  this->fps_history.push_back(fps);
  if (this->fps_history.size() > (unsigned int)this->fps_history_max_len) {
    this->fps_history.pop_front();
  }

  double tot = 0.0;
  for (auto fps : this->fps_history)
    tot += fps;

  return tot / ((double) this->fps_history.size());
}

bool Renderer::frameEnded(const Ogre::FrameEvent &evt)
{
  this->time += evt.timeSinceLastFrame;
  auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
  auto anim = scene_manager->getAnimation("anim");
  anim->apply(this->time);
  std::cerr << this->time << std::endl;
  return true;
}
