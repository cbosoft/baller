#include "simrenderer.hpp"


void Renderer::setup()
{
  // do not forget to call the base first
  OgreBites::ApplicationContext::setup();
  this->addInputListener(this);

  Ogre::Root* root = this->getRoot();
  Ogre::SceneManager* scene_manager = root->createSceneManager("DefaultSceneManager", "mainSceneManager");

  Ogre::RTShader::ShaderGenerator* shadergen = 
    Ogre::RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scene_manager);

  scene_manager->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));

  Ogre::Light* top_light = scene_manager->createLight("topLight");
  Ogre::SceneNode* topLightNode = scene_manager->getRootSceneNode()->createChildSceneNode("topLightNode");
  topLightNode->attachObject(top_light);
  top_light->setDiffuseColour(1.0, 0.5, 0.5);
  topLightNode->setPosition(0, 100, 0);

  Ogre::Light* bottom_light = scene_manager->createLight("bottomLight");
  Ogre::SceneNode* bottomLightNode = scene_manager->getRootSceneNode()->createChildSceneNode("bottomLightNode");
  bottomLightNode->attachObject(bottom_light);
  bottom_light->setDiffuseColour(0.5, 0.5, 1.0);
  bottomLightNode->setPosition(0, -100, 0);

  Ogre::SceneNode* camNode = scene_manager->getRootSceneNode()->createChildSceneNode("cameraNode");
  Ogre::SceneNode* origNode = scene_manager->getRootSceneNode()->createChildSceneNode("originNode");
  origNode->setPosition(0.0, 0.0, 0.0);

  Ogre::Camera* cam = scene_manager->createCamera("mainCam");
  cam->setNearClipDistance(5); // specific to this sample
  cam->setAutoAspectRatio(true);
  camNode->attachObject(cam);
  camNode->setAutoTracking(true, origNode);
  double c = std::sqrt(3.0);
  camNode->setPosition(c*this->cam_dist, c*this->cam_dist, c*this->cam_dist);

  this->getRenderWindow()->addViewport(cam);






}
