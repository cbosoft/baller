#include "maths_util.hpp"

double de_reflex(double angle)
{
  while (angle > M_PI_2)
    angle -= M_PI_2;

  return angle;
}

double rad2deg(double rad)
{
  return rad*180.0/M_PI;
}

double deg2rad(double deg)
{
  return deg*M_PI/180.0;
}

Ogre::Quaternion eul2quat(double phi, double theta, double psi)
{
  double phi2 = phi*0.5, theta2 = theta*0.5, psi2 = psi*0.5;
  double cosphi2 = std::cos(phi2), costheta2 = std::cos(theta2), cospsi2 = std::cos(psi2);
  double sinphi2 = std::sin(phi2), sintheta2 = std::sin(theta2), sinpsi2 = std::sin(psi2);
  double w = cosphi2*costheta2*cospsi2 + sinphi2*sintheta2*sinpsi2;
  double y = sinphi2*costheta2*cospsi2 - cosphi2*sintheta2*sinpsi2;
  double x = cosphi2*sintheta2*cospsi2 + sinphi2*costheta2*sinpsi2;
  double z = cosphi2*costheta2*sinpsi2 - sinphi2*sintheta2*cospsi2;
  return Ogre::Quaternion(w, x, y, z);
}
