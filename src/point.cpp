#include <iostream>

#include "point.hpp"


Point::Point(OgreBites::ApplicationContext *ctxt, Ogre::Vector3 position, Ogre::Vector3 velocity, double radius, double sim_side_length)
{
  this->positions.push_back(position);
  this->velocities.push_back(velocity);
  this->times.push_back(0.0);
  this->r = radius;
  this->ctxt = ctxt;
  this->L = sim_side_length;

  auto scene_manager = this->ctxt->getRoot()->getSceneManager("mainSceneManager");
  Ogre::Entity* ballEntity = scene_manager->createEntity("sphere.mesh"); // default diameter 100 units
  this->node = scene_manager->getRootSceneNode()->createChildSceneNode();
  this->node->attachObject(ballEntity);
  this->node->setPosition(position);
  this->node->setScale(r/100.0, r/100.0, r/100.0);
  std::cerr << this->node->getPosition() << r/100.0 << std::endl;
}

void Point::add_timepoint(Ogre::Vector3 position, Ogre::Vector3 velocity, double time)
{
  this->positions.push_back(position);
  this->velocities.push_back(velocity);
  this->times.push_back(time);
}

Ogre::Vector3 Point::get_velocity(int timestep) const
{
  return this->velocities[timestep];
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
  if (tprime > this->get_time(i)) i++;

  double dt = tprime - this->get_time(i);
  Ogre::Vector3 position = this->get_position(i) + (this->get_velocity(i)*dt);
  // for (int i = 0; i < 3 ; i++) {
  //   if (position[i] < 0) position[i] += this->L;
  //   if (position[i] > this->L) position[i] -= this->L;
  // }

  this->node->setPosition(position);

}
