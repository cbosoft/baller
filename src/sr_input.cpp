#include "simrenderer.hpp"


bool Renderer::keyPressed(const OgreBites::KeyboardEvent &evt)
{
  switch(evt.keysym.sym) {
    case OgreBites::SDLK_ESCAPE:
      this->getRoot()->queueEndRendering();
      break;

    case '=':
    case 'r':
      this->reset_camera();
      break;

    case 'w': this->keys_down |= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_PP : DK_U; break;
    case 'a': this->keys_down |= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_NY : DK_L; break;
    case 's': this->keys_down |= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_NP : DK_D; break;
    case 'd': this->keys_down |= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_PY : DK_R; break;
    case 'q': this->keys_down |= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_NR : DK_F; break;
    case 'e': this->keys_down |= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_PR : DK_B; break;

  }


  double dx = 0.0, dy = 0.0, dz = 0.0, dyaw = 0.0, dpitch = 0.0, droll = 0.0;
  if (this->keys_down & DK_L) dx -= this->pan_speed;
  if (this->keys_down & DK_R) dx += this->pan_speed;
  if (this->keys_down & DK_U) dy += this->pan_speed;
  if (this->keys_down & DK_D) dy -= this->pan_speed;
  if (this->keys_down & DK_F) dz -= this->pan_speed;
  if (this->keys_down & DK_B) dz += this->pan_speed;

  if (this->keys_down & DK_NY) dyaw -= this->rot_speed;
  if (this->keys_down & DK_PY) dyaw += this->rot_speed;
  if (this->keys_down & DK_PP) dpitch += this->rot_speed;
  if (this->keys_down & DK_NP) dpitch -= this->rot_speed;
  if (this->keys_down & DK_PR) droll += this->rot_speed;
  if (this->keys_down & DK_NR) droll -= this->rot_speed;

  //this->rotate_camera(dyaw, dpitch, droll);
  this->move_camera(dx, dy, dz);

  return true;
}

bool Renderer::keyReleased(const OgreBites::KeyboardEvent &evt)
{
  switch(evt.keysym.sym) {

    // case 'w': this->keys_down ^= DK_U; break;
    // case 'a': this->keys_down ^= DK_L; break;
    // case 's': this->keys_down ^= DK_D; break;
    // case 'd': this->keys_down ^= DK_R; break;
    // case 'q': this->keys_down ^= DK_F; break;
    // case 'e': this->keys_down ^= DK_B; break;
    // case 'W': this->keys_down ^= DK_PP; break;
    // case 'A': this->keys_down ^= DK_NY; break;
    // case 'S': this->keys_down ^= DK_NP; break;
    // case 'D': this->keys_down ^= DK_PY; break;
    // case 'Q': this->keys_down ^= DK_NR; break;
    // case 'E': this->keys_down ^= DK_PR; break;
    case 'w': this->keys_down ^= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_PP : DK_U; break;
    case 'a': this->keys_down ^= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_NY : DK_L; break;
    case 's': this->keys_down ^= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_NP : DK_D; break;
    case 'd': this->keys_down ^= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_PY : DK_R; break;
    case 'q': this->keys_down ^= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_NR : DK_F; break;
    case 'e': this->keys_down ^= (evt.keysym.mod & OgreBites::KMOD_SHIFT) ? DK_PR : DK_B; break;

    case 'o':
      this->look_at_origin();
      break;

  }


  return true;
}

bool Renderer::mouseMoved(const OgreBites::MouseMotionEvent &evt)
{
  if (this->mouse_camera_control) {
    this->rotate_camera(evt.xrel, evt.yrel, 0.0);
  }
  return true;
}

bool Renderer::mouseWheelRolled(const OgreBites::MouseWheelEvent &evt)
{
  this->cam_dist += evt.y * this->zoom_mult;
  this->rotate_camera(0.0, 0.0, 0.0);
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
