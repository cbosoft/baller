#include <iostream>

#include "point.hpp"


Point::Point(OgreBites::ApplicationContext *ctxt, Ogre::Vector3 position, Ogre::Vector3 velocity, double radius, int id)
{
  this->positions.push_back(position);
  this->velocities.push_back(velocity);
  this->r = radius;
  this->ctxt = ctxt;
  this->id = id;

  auto scene_manager = this->ctxt->getRoot()->getSceneManager("mainSceneManager");
  this->entity = scene_manager->createEntity("sphere.mesh"); // default diameter 100 units
  this->entity->getSubEntity(0)->setMaterialName("normalMaterial");
  this->node = scene_manager->getRootSceneNode()->createChildSceneNode();
  this->node->attachObject(this->entity);
  this->node->setScale(r/100.0, r/100.0, r/100.0);
}

void Point::add_timepoint(Ogre::Vector3 position, Ogre::Vector3 velocity)
{
  this->positions.push_back(position);
  this->velocities.push_back(velocity);
}

Ogre::Vector3 Point::get_velocity(int timestep) const
{
  return this->velocities[timestep];
}

Ogre::Vector3 Point::get_position(int timestep) const
{
  return this->positions[timestep];
}

Ogre::SceneNode *Point::get_node() const
{
  return this->node;
}

void Point::set_position(Ogre::Vector3 pos)
{
  this->node->setPosition(pos);
}

void Point::set_interacting(bool v)
{
  if (v) {
    this->entity->getSubEntity(0)->setMaterialName("interactingMaterial");
  }
  else {
    this->entity->getSubEntity(0)->setMaterialName("normalMaterial");
  }
}

int Point::get_id() const
{
  return this->id;
}
