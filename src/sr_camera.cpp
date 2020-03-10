#include "simrenderer.hpp"
#include "maths_util.hpp"


void Renderer::orbit_camera(double dx, double dy, double dz)
{
  auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
  Ogre::SceneNode *origin_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("originNode");
  Ogre::SceneNode *cam_node = (Ogre::SceneNode *)origin_node->getChild("cameraNode");
  Ogre::Camera *cam = (Ogre::Camera *)cam_node->getAttachedObject("mainCamera");

  origin_node->yaw(Ogre::Degree(-dx * 0.25));
  origin_node->pitch(Ogre::Degree(-dy * 0.25));

  this->cam_dist += dz;
  cam->setPosition(origin_node->getPosition());
  cam->moveRelative({0, 0, this->cam_dist});
}


void Renderer::reset_camera()
{
  auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
  Ogre::SceneNode *origin_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("originNode");
  Ogre::SceneNode *cam_node = (Ogre::SceneNode *)origin_node->getChild("cameraNode");
  Ogre::Camera *cam = (Ogre::Camera *)cam_node->getAttachedObject("mainCamera");

  origin_node->yaw(Ogre::Degree(0.0));
  origin_node->pitch(Ogre::Degree(0.0));

  this->cam_dist = this->cam_dist_default;
  cam->setPosition(origin_node->getPosition());
  cam->moveRelative({0, 0, this->cam_dist});
}
