#include <sstream>

#include "simrenderer.hpp"
#include "textrenderer.hpp"


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
  this->time += this->time_mult*evt.timeSinceLastFrame;
  for (auto point : this->points) {
    point.apply(this->time);
  }

  double fps = this->add_fps_get_av(1.0/evt.timeSinceLastFrame);

  static int i = 0;

  if (i > this->overlay_frames_skip) {
    std::stringstream ss;
    ss
      << " some stats " << std::endl
      << "fps: " << fps << std::endl 
      << "  t: " << this->time;
    TextRenderer::getSingleton().setText("disp", ss.str());
    i = 0;
  }

  i++;
  return true;
}
