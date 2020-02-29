#include <iostream>

#include "point.hpp"

static unsigned short handlec = 0;

Point::Point(OgreBites::ApplicationContext *ctxt, Ogre::Vector3 position, double radius)
{
  this->positions.push_back(position);
  this->times.push_back(0.0);
  this->r = radius;
  this->ctxt = ctxt;

  auto scene_manager = this->ctxt->getRoot()->getSceneManager("mainSceneManager");
  Ogre::Entity* ballEntity = scene_manager->createEntity("sphere.mesh"); // default diameter 100 units
  this->node = scene_manager->getRootSceneNode()->createChildSceneNode();
  this->node->attachObject(ballEntity);
  this->node->setPosition(position);
  this->node->setScale(r/200.0, r/200.0, r/200.0);
  std::cerr << this->node->getPosition() << r/200.0 << std::endl;
}

void Point::add_timepoint(Ogre::Vector3 position, double time)
{
  this->positions.push_back(position);
  this->times.push_back(time);
}

Ogre::Vector3 Point::get_position(int timestep) const
{
  return this->positions[timestep];
}

double Point::get_time(int timestep) const
{
  return this->times[timestep];
}

Ogre::SceneNode *Point::get_node() const
{
  return this->node;
}

void Point::apply(double t)
{
  //this->track->apply(Ogre::TimeIndex(t));
  static unsigned int i = 1;
  static double toff = 0.0;
  if (i >= this->positions.size()) {
    i = 1; // restart, or end? TODO
    toff += this->times.back();
  }
  double tprime = t-toff;

  Ogre::Vector3 velocity = (this->get_position(i) - this->get_position(i-1)) / (this->get_time(i) - this->get_time(i-1));
  double dt = tprime - this->get_time(i);
  this->node->setPosition(this->get_position(i) + (velocity*dt));
  if (tprime > this->get_time(i)) i++;
}
