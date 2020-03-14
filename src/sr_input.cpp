#include "simrenderer.hpp"


bool Renderer::keyPressed(const OgreBites::KeyboardEvent &evt)
{
  switch(evt.keysym.sym) {
    case OgreBites::SDLK_ESCAPE:
      this->getRoot()->queueEndRendering();
      break;

    case '=':
      this->reset_camera();
      break;

    case 'r':
      this->repeat = !this->repeat;
      break;

    case 'w': this->keys_down |= DK_U; break;
    case 'a': this->keys_down |= DK_L; break;
    case 's': this->keys_down |= DK_D; break;
    case 'd': this->keys_down |= DK_R; break;
    case 'q': this->keys_down |= DK_F; break;
    case 'e': this->keys_down |= DK_B; break;

  }


  double dx = 0.0, dy = 0.0, dz = 0.0;
  if (this->keys_down & DK_L) dx -= this->orbit_speed;
  if (this->keys_down & DK_R) dx += this->orbit_speed;
  if (this->keys_down & DK_U) dy += this->orbit_speed;
  if (this->keys_down & DK_D) dy -= this->orbit_speed;
  if (this->keys_down & DK_F) dz -= this->orbit_speed*this->zoom_mult;
  if (this->keys_down & DK_B) dz += this->orbit_speed*this->zoom_mult;

  this->orbit_camera(dx, dy, dz);

  return true;
}

bool Renderer::keyReleased(const OgreBites::KeyboardEvent &evt)
{
  switch(evt.keysym.sym) {

    case 'w': this->keys_down ^= DK_U; break;
    case 'a': this->keys_down ^= DK_L; break;
    case 's': this->keys_down ^= DK_D; break;
    case 'd': this->keys_down ^= DK_R; break;
    case 'q': this->keys_down ^= DK_F; break;
    case 'e': this->keys_down ^= DK_B; break;

  }

  return true;
}

bool Renderer::mouseMoved(const OgreBites::MouseMotionEvent &evt)
{
  if (this->mouse_camera_control) {
    this->orbit_camera(evt.xrel, evt.yrel, 0.0);
  }
  return true;
}

bool Renderer::mouseWheelRolled(const OgreBites::MouseWheelEvent &evt)
{
  this->orbit_camera(0.0, 0.0, evt.y*this->zoom_mult);
  return true;
}

bool Renderer::mousePressed(const OgreBites::MouseButtonEvent &evt)
{
  (void) evt;
  this->mouse_camera_control = true;
  return true;
}

bool Renderer::mouseReleased(const OgreBites::MouseButtonEvent &evt)
{
  (void) evt;
  this->mouse_camera_control = false;
  return true;
}
