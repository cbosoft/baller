#pragma once
#include <vector>

#include <Ogre.h>
#include "OgreApplicationContext.h"

class Point {
  private:
    std::vector<Ogre::Vector3> positions;
    std::vector<Ogre::Vector3> velocities;
    std::vector<double> times;
    double r, hL;
    Ogre::SceneNode *node;
    OgreBites::ApplicationContext *ctxt;


  public:
    Point(OgreBites::ApplicationContext *ctxt, Ogre::Vector3 velocity, Ogre::Vector3 position, double radius, double sim_side_length);
    void add_timepoint(Ogre::Vector3 position, Ogre::Vector3 velocity, double time);

    Ogre::Vector3 get_position(int timestep) const;
    Ogre::Vector3 get_velocity(int timestep) const;
    double get_time(int timestep) const;

    Ogre::SceneNode *get_node() const;
    void apply(double t);

};
