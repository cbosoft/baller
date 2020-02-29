#pragma once
#include <vector>
#include <Ogre.h>

class Point {
  private:
    std::vector<Ogre::Vector3> positions;
    double r;


  public:
    Point();
    Point(double x, double y, double z, double r);
    void add_timepoint(double x, double y, double z);

    Ogre::Vector3 get_position(int timestep) const;

};
