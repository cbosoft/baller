#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>
#include <cmath>

enum Direction {
  DIR_X,
  DIR_Y,
  DIR_Z,
};

enum DIR_KEYS {
  DK_L = 1 << 0,
  DK_R = 1 << 1,
  DK_U = 1 << 2,
  DK_D = 1 << 3
};

class Renderer : public OgreBites::ApplicationContext, public OgreBites::InputListener {
  private:
    bool mouse_camera_control;
    double cam_dist;
    double yaw;
    double pitch;
    double rot_speed = 10.0;
    double zoom_mult = 10.0;

    int keys_down;

  public:
    Renderer() : OgreBites::ApplicationContext("renderer")
    {
      this->mouse_camera_control = false;
      this->cam_dist = 1000;
      this->yaw = 0.0;
      this->pitch = M_PI_4;
      this->keys_down = 0;
    };
    virtual ~Renderer() {}

    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    bool keyReleased(const OgreBites::KeyboardEvent& evt);
    bool mouseMoved(const OgreBites::MouseMotionEvent &evt);
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent &evt);
    bool mousePressed(const OgreBites::MouseButtonEvent &evt);
    bool mouseReleased(const OgreBites::MouseButtonEvent &evt);

    void move_camera(Direction d, double distance);
    void rotate_camera(double, double);
    void reset_camera();
};


void Renderer::setup()
{
  // do not forget to call the base first
  OgreBites::ApplicationContext::setup();
    this->addInputListener(this);

    Ogre::Root* root = this->getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager("DefaultSceneManager", "mainSceneManager");

    Ogre::RTShader::ShaderGenerator* shadergen = 
      Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    scnMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    Ogre::Light* top_light = scnMgr->createLight("topLight");
    Ogre::SceneNode* topLightNode = scnMgr->getRootSceneNode()->createChildSceneNode("topLightNode");
    topLightNode->attachObject(top_light);
    top_light->setDiffuseColour(1.0, 0.5, 0.5);
    topLightNode->setPosition(0, 10000, 0);


    Ogre::Light* bottom_light = scnMgr->createLight("bottomLight");
    Ogre::SceneNode* bottomLightNode = scnMgr->getRootSceneNode()->createChildSceneNode("bottomLightNode");
    bottomLightNode->attachObject(bottom_light);
    bottom_light->setDiffuseColour(0.5, 0.5, 1.0);
    bottomLightNode->setPosition(0, -10000, 0);

    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode("cameraNode");
    Ogre::SceneNode* origNode = scnMgr->getRootSceneNode()->createChildSceneNode("orginNode");
    origNode->setPosition(0.0, 0.0, 0.0);

    Ogre::Camera* cam = scnMgr->createCamera("mainCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setAutoTracking(true, origNode);

    this->getRenderWindow()->addViewport(cam);

    double s = 300;
    for (int x = -1; x < 2; x++) {
      for (int y = -1; y < 2; y++) {
        for (int z = -1; z < 2; z++) {
          Ogre::Entity* ballEntity = scnMgr->createEntity("sphere.mesh");
          Ogre::SceneNode* ballNode = scnMgr->getRootSceneNode()->createChildSceneNode();
          ballNode->attachObject(ballEntity);
          ballNode->setPosition(x*s, y*s, z*s);
        }
      }
    }

    camNode->setPosition(0, 0, this->cam_dist);
}


bool Renderer::keyPressed(const OgreBites::KeyboardEvent &evt)
{
  switch(evt.keysym.sym) {
    case 'q':
    case OgreBites::SDLK_ESCAPE:
      this->getRoot()->queueEndRendering();
      break;

    case '=':
    case 'r':
      this->reset_camera();
      break;

    case 'w':
      this->keys_down |= DK_U;
      break;

    case 'a':
      this->keys_down |= DK_L;
      break;

    case 's':
      this->keys_down |= DK_D;
      break;

    case 'd':
      this->keys_down |= DK_R;
      break;
  }


  double dx = 0.0, dy = 0.0;
  if (this->keys_down & DK_L) dx -= this->rot_speed;
  if (this->keys_down & DK_R) dx += this->rot_speed;
  if (this->keys_down & DK_U) dy += this->rot_speed;
  if (this->keys_down & DK_D) dy -= this->rot_speed;

  this->rotate_camera(dx, dy);

  return true;
}

bool Renderer::keyReleased(const OgreBites::KeyboardEvent &evt)
{
  switch(evt.keysym.sym) {
    case 'q':
    case OgreBites::SDLK_ESCAPE:
      this->getRoot()->queueEndRendering();
      break;

    case 'w':
      this->keys_down ^= DK_U;
      break;

    case 'a':
      this->keys_down ^= DK_L;
      break;

    case 's':
      this->keys_down ^= DK_D;
      break;

    case 'd':
      this->keys_down ^= DK_R;
      break;
  }


  return true;
}

bool Renderer::mouseMoved(const OgreBites::MouseMotionEvent &evt)
{
  if (this->mouse_camera_control) {
    this->rotate_camera(evt.xrel, evt.yrel);
  }
  return true;
}

bool Renderer::mouseWheelRolled(const OgreBites::MouseWheelEvent &evt)
{
  this->cam_dist += evt.y * this->zoom_mult;
  this->rotate_camera(0.0, 0.0);
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



void Renderer::move_camera(Direction direction, double distance)
{
  auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
  auto cam_node = scene_manager->getRootSceneNode()->getChild("cameraNode");

  Ogre::Vector3 v;
  switch (direction) {

    case DIR_X:
      v = Ogre::Vector3(distance, 0.0, 0.0);
      break;

    case DIR_Y:
      v = Ogre::Vector3(0.0, distance, 0.0);
      break;

    case DIR_Z:
      v = Ogre::Vector3(0.0, 0.0, distance);
      break;

  }
  
  cam_node->translate(v);

  return;
}


void Renderer::reset_camera()
{
  auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
  Ogre::SceneNode *cam_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("cameraNode");
  this->pitch = M_PI_4;
  this->yaw = 0.0;
  cam_node->setPosition(Ogre::Vector3(0.0, 0.0, cam_dist));
  cam_node->lookAt(Ogre::Vector3(0.0, 0.0, 0.0), Ogre::Node::TS_WORLD);
  return;
}


void Renderer::rotate_camera(double cam_dx, double cam_dy)
{
    double dx = 0.0, dy = 0.0, dz = 0.0;
    double dyaw = M_PI - (2.0*std::acos(cam_dx/(this->cam_dist*2)));
    //double dyaw = cam_dx * 0.001;
    this->yaw += dyaw;
    if (this->yaw > 2*M_PI) {
      this->yaw -= 2*M_PI;
    }
    else if (this->yaw < 0.0) {
      this->yaw += 2*M_PI;
    }

    double dpitch = M_PI - (2.0*std::acos(cam_dy/(this->cam_dist*2)));
    //double dpitch = -cam_dy * 0.001;
    this->pitch -= dpitch;
    if (this->pitch > 2*M_PI) {
      this->pitch -= 2*M_PI;
    }
    else if (this->pitch < 0.0) {
      this->pitch += 2*M_PI;
    }
    double R_prime = std::cos(M_PI_4 - this->pitch) * this->cam_dist;
    dy = std::sin(M_PI_4 - this->pitch)*this->cam_dist;
    dx = std::cos(this->yaw) * R_prime;
    dz = std::sin(this->yaw) * R_prime;
    



    Ogre::Vector3 vec(dx, dy, dz);
    auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
    Ogre::SceneNode *cam_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("cameraNode");
    cam_node->setPosition(vec);
    //cam_node->setOrientation(Ogre::Quaternion());
    //cam_node->lookAt(Ogre::Vector3(0.0, 0.0, 0.0), Ogre::Node::TS_WORLD);
}


int main(void) //int argc, char **argv)
{
  try
  {
  	Renderer app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error occurred during execution: " << e.what() << '\n';
    return 1;
  }

  return 0;
}

//! [fullsource]
