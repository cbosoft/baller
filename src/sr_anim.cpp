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
  static int i = 1, j = 0;
  while (this->times[i] < this->time) i++;
  if (i > (int)this->times.size()) {
    if (this->repeat) {
      this->time = 0.0;
      i = 1;
    }
    else {
      return true;
    }
  }

  this->time += this->time_mult*evt.timeSinceLastFrame * this->speed_mult;
  double dt = this->time - this->times[i-1];
  auto pair = this->interacting_ids[i];
  int aid = pair.first;
  int bid = pair.second;
  for (auto &point : this->points) {
    auto p = point.get_position(i-1) + point.get_velocity(i-1) * dt;
    for (int i = 0; i < 3; i++) {
      if (p[i] < 0.0) p[i] += this->sim_side_length;
      else if (p[i] > this->sim_side_length) p[i] -= this->sim_side_length;
    }
    point.set_position(p - this->sim_side_length/2);
    point.set_interacting(point.get_id() == aid || point.get_id() == bid);
  }

  double fps = this->add_fps_get_av(1.0/evt.timeSinceLastFrame);

  if (j > this->overlay_frames_skip) {
    std::stringstream ss;
    ss
      << "      t: " << this->time << std::endl
      << "      n: " << this->points.size() << std::endl
      << "    fps: " << fps << std::endl 
      << " repeat: " << (this->repeat?"true":"false") << std::endl
      << "  speed: " << this->speed_mult << std::endl
      << "cam pos: " << this->cam_dist << std::endl
      ;
    TextRenderer::getSingleton().setText("disp", ss.str());
    j = 0;
  }

  j++;
  return true;
}
