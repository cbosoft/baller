#include "simrenderer.hpp"


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
    Ogre::SceneNode* origNode = scnMgr->getRootSceneNode()->createChildSceneNode("originNode");
    origNode->setPosition(0.0, 0.0, 0.0);

    Ogre::Camera* cam = scnMgr->createCamera("mainCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setAutoTracking(true, origNode);
    double c = std::sqrt(3.0);
    camNode->setPosition(c*this->cam_dist, c*this->cam_dist, c*this->cam_dist);

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

    Ogre::Entity* ballEntity = scnMgr->createEntity("sphere.mesh");
    Ogre::SceneNode* ballNode = scnMgr->getRootSceneNode()->createChildSceneNode("objNode");
    ballNode->attachObject(ballEntity);
    ballNode->setPosition(0.0, 0.0, this->cam_dist);

}
