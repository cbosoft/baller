#pragma once
#include <OgreQuaternion.h>
#include <cmath>

double de_reflex(double angle);
double rad2deg(double rad);
double deg2rad(double deg);

Ogre::Quaternion ypr2quat(double yaw, double pitch, double roll);
Ogre::Quaternion eul2quat(double alpha, double beta, double gamma);
