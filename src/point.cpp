#include "point.hpp"

Point::Point()
{
  this->r = 1.0;
}

Point::Point(double x, double y, double z, double r)
{
  this->positions.push_back(Ogre::Vector3(x, y, z));
  this->r = r;
}

Ogre::Vector3 get_position(int timestep)
{
  return this->positions[timestep];
}
