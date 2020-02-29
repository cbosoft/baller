#include "simrenderer.hpp"
#include "maths_util.hpp"


void Renderer::reset_camera()
{
  auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
  Ogre::SceneNode *cam_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("cameraNode");
  cam_node->setPosition(Ogre::Vector3(0.0, 0.0, cam_dist));
  cam_node->lookAt(Ogre::Vector3(0.0, 0.0, 0.0), Ogre::Node::TS_WORLD);
  return;
}


void Renderer::rotate_camera(double dyaw, double dpitch, double droll)
{
    auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
    Ogre::SceneNode *cam_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("cameraNode");
    Ogre::Quaternion h = cam_node->getOrientation();
    cam_node->setOrientation(eul2quat(h.getYaw().valueRadians()+dyaw, h.getPitch().valueRadians()+dpitch, h.getRoll().valueRadians()+droll));
}


void Renderer::move_camera(double dx, double dy, double dz)
{
    auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
    Ogre::SceneNode *cam_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("cameraNode");
    Ogre::Vector3 vec(dx, dy, dz);
    cam_node->setPosition(vec+cam_node->getPosition());
}

void Renderer::look_at_origin()
{
    auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
    Ogre::SceneNode *cam_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("cameraNode");
    Ogre::SceneNode *origin_node = (Ogre::SceneNode *)scene_manager->getRootSceneNode()->getChild("originNode");
    cam_node->lookAt(origin_node->getPosition(), Ogre::Node::TS_WORLD);
}
