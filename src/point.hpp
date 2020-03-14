#pragma once
#include <vector>

#include <Ogre.h>
#include "OgreApplicationContext.h"

class Renderer;
class Point {
  private:
    std::vector<Ogre::Vector3> positions;
    std::vector<Ogre::Vector3> velocities;
    double r;
    int id;
    Ogre::SceneNode *node;
    OgreBites::ApplicationContext *ctxt;
    Renderer *parent;
    Ogre::Entity *entity;


  public:
    Point(OgreBites::ApplicationContext *ctxt, Ogre::Vector3 velocity, Ogre::Vector3 position, double radius, int id);
    void add_timepoint(Ogre::Vector3 position, Ogre::Vector3 velocity);

    int get_id() const;
    Ogre::Vector3 get_position(int timestep) const;
    Ogre::Vector3 get_velocity(int timestep) const;
    double get_time(int timestep) const;


    Ogre::SceneNode *get_node() const;
    void set_position(Ogre::Vector3 pos);
    void set_interacting(bool v);

};
