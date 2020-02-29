#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreOverlaySystem.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"

#include "point.hpp"
#include "textrenderer.hpp"

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
    double time_mult;
    double time;

    int keys_down;

    TextRenderer *tr;

    std::list<double> fps_history;
    int fps_history_max_len;
    int overlay_frames_skip;

    std::string trajectory_path;
    std::vector<Point> points;


    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    bool keyReleased(const OgreBites::KeyboardEvent& evt);
    bool mouseMoved(const OgreBites::MouseMotionEvent &evt);
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent &evt);
    bool mousePressed(const OgreBites::MouseButtonEvent &evt);
    bool mouseReleased(const OgreBites::MouseButtonEvent &evt);
    bool frameEnded(const Ogre::FrameEvent &evt);
    void load_trajectory();

    void rotate_camera(double dyaw, double dpitch, double droll);
    void move_camera(double dx, double dy, double dz);
    void look_at_origin();
    void reset_camera();

  public:
    Renderer(std::string trajectory_path, double camera_distance, double rotation_speed, double pan_speed, double zoom_mult) : OgreBites::ApplicationContext("renderer")
    {
      this->trajectory_path = trajectory_path;
      this->cam_dist = camera_distance;
      this->rot_speed = rotation_speed;
      this->pan_speed = pan_speed;
      this->zoom_mult = zoom_mult;

      this->mouse_camera_control = false;
      this->keys_down = 0;
      this->time = 0.0;
      this->fps_history_max_len = 100;
      this->overlay_frames_skip = 10;
      this->time_mult = 0.1;
    };

    void init_overlay() {
      auto root = Ogre::Root::getSingletonPtr();
      auto scene_manager = root->getSceneManager("mainSceneManager");
      scene_manager->addRenderQueueListener(this->getOverlaySystem());

      this->tr = new TextRenderer();
      this->tr->addTextBox("disp", " ", 10, 10, 100, 100, Ogre::ColourValue::Green);
    }

    virtual ~Renderer() {
      if (this->tr) 
        delete this->tr;
    }

    double add_fps_get_av(double fps);

};
