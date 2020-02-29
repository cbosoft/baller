#pragma once
#include <vector>

#include <Ogre.h>
#include "OgreApplicationContext.h"

class Point {
  private:
    std::vector<Ogre::Vector3> positions;
    std::vector<double> times;
    double r;
    Ogre::SceneNode *node;
    OgreBites::ApplicationContext *ctxt;


  public:
    Point(OgreBites::ApplicationContext *ctxt, Ogre::Vector3 position, double radius);
    void add_timepoint(Ogre::Vector3 position, double time);

    Ogre::Vector3 get_position(int timestep) const;
    double get_time(int timestep) const;

    Ogre::SceneNode *get_node() const;
    void apply(double t);

};
