#pragma once

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>
#include <cmath>

enum DIR_KEYS {
  DK_L = 1 << 0,
  DK_R = 1 << 1,

  DK_U = 1 << 2,
  DK_D = 1 << 3,

  DK_F = 1 << 4,
  DK_B = 1 << 5,

  DK_PY = 1 << 6,
  DK_NY = 1 << 7,

  DK_PP = 1 << 8,
  DK_NP = 1 << 9,

  DK_PR = 1 << 10,
  DK_NR = 1 << 11
};

class Renderer : public OgreBites::ApplicationContext, public OgreBites::InputListener {
  private:
    bool mouse_camera_control;
    double cam_dist;
    double rot_speed;
    double pan_speed;
    double zoom_mult;
    std::list<Ogre::SceneNode *> point_nodes;

    int keys_down;

    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    bool keyReleased(const OgreBites::KeyboardEvent& evt);
    bool mouseMoved(const OgreBites::MouseMotionEvent &evt);
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent &evt);
    bool mousePressed(const OgreBites::MouseButtonEvent &evt);
    bool mouseReleased(const OgreBites::MouseButtonEvent &evt);

    void rotate_camera(double dyaw, double dpitch, double droll);
    void move_camera(double dx, double dy, double dz);
    void look_at_origin();
    void reset_camera();

  public:
    Renderer(double camera_distance, double rotation_speed, double pan_speed, double zoom_mult) : OgreBites::ApplicationContext("renderer")
    {
      this->mouse_camera_control = false;
      this->keys_down = 0;

      this->cam_dist = camera_distance;
      this->rot_speed = rotation_speed;
      this->pan_speed = pan_speed;
      this->zoom_mult = zoom_mult;
    };
    virtual ~Renderer() {}

    void load_trajectory(std::string path);
};
