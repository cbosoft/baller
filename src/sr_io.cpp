#include <fstream>
#include <regex>
#include <iomanip>

#include "simrenderer.hpp"
#include "point.hpp"

const std::regex STEP_RE("^ - step:$");
const std::regex TIME_RE("^   time: ([\\d.\\-e+]*)$");
const std::regex DASH_RE("^      - ?$");
const std::regex   ID_RE("^        id: (\\d*)$");
const std::regex MASS_RE("^        mass: (\\d*)$");
const std::regex DIAM_RE("^        diameter: (\\d*)$");
const std::regex  POS_RE("^        position: \\[([\\d.\\-e+]*), ([\\d.\\-e+]*), ([\\d.\\-e+]*)\\]$");
const std::regex  VEL_RE("^        velocity: \\[([\\d.\\-e+]*), ([\\d.\\-e+]*), ([\\d.\\-e+]*)\\]$");

void Renderer::load_trajectory_from_yaml()
{
  // traj in yaml format
  // list of steps, which are dicts of time, and balls
  // balls is list of balls
  /*
  
  |---
  | - step:
  |   time: 0
  |   balls:
  |      - 
  |        id: 1
  |        mass: 1
  |        diameter: 1
  |        position: []
          ...
  */

  std::ifstream ifs(this->trajectory_path);
  std::string line;

  // (id-1) is index in this->points

  // gobble first line '---'
  std::getline(ifs, line);

  //bool reading_step = false;
  //bool reading_ball
  std::cerr << "parsing yaml" << std::endl;
  std::smatch match;
  float time = 0.0, rx = 0.0, ry = 0.0, rz = 0.0, vx = 0.0, vy = 0.0, vz = 0.0, diameter = 0.0;
  int id = 0, step = -1;

  while (getline(ifs, line)) {
    std::cerr << line << std::endl;
    if (std::regex_match(line, match, STEP_RE)) {
step_read:
      step++;
      // TIME
      if (!getline(ifs, line)) goto corrupt_yaml;
      if (std::regex_match(line, match, TIME_RE)) {
        time = atof(match.str(1).c_str());
        std::cerr << "reading timestep: " << time << std::endl; 
      }
      else {
corrupt_yaml:
        std::cerr << "corrupt yaml: " << line << std::endl;
        exit(1);
      }

      if (!getline(ifs, line)) goto corrupt_yaml;
      if (!getline(ifs, line)) goto corrupt_yaml;

      // BALLS
      while (true) {
        // ID
        if (!getline(ifs, line)) goto corrupt_yaml;
        if (std::regex_match(line, match, ID_RE)) {
          id = atoi(match.str(1).c_str());
        }

        if (!getline(ifs, line)) goto corrupt_yaml; // gobble mass

        if (!getline(ifs, line)) goto corrupt_yaml;
        if (std::regex_match(line, match, DIAM_RE)) {
          diameter = atof(match.str(1).c_str());
        }

        // POSITION
        if (!getline(ifs, line)) goto corrupt_yaml;
        //std::cerr << "pos?" << line << std::endl;
        if (std::regex_match(line, match, POS_RE)) {
          //std::cerr << match.str(1) << ", " << match.str(2) << ", " << match.str(3) << std::endl;
          rx = atof(match.str(1).c_str());
          ry = atof(match.str(2).c_str());
          rz = atof(match.str(3).c_str());
          //std::cerr << x << ", " << y << ", " << z << std::endl;
        }

        // VELOCITY
        if (!getline(ifs, line)) goto corrupt_yaml;
        //std::cerr << "pos?" << line << std::endl;
        if (std::regex_match(line, match, VEL_RE)) {
          //std::cerr << match.str(1) << ", " << match.str(2) << ", " << match.str(3) << std::endl;
          vx = atof(match.str(1).c_str());
          vy = atof(match.str(2).c_str());
          vz = atof(match.str(3).c_str());
          //std::cerr << x << ", " << y << ", " << z << std::endl;
        }

        if (step) {
          this->points[id-1].add_timepoint({rx, ry, rz}, {vx, vy, vz}, time);
        }
        else {
          Point p(this, {rx, ry, rz}, {vx, vy, vz}, diameter/2.0, 10);
          this->points.push_back(p);
        }

        while (true) {

          if (!getline(ifs, line)) {
            goto finished;
          }

          if (std::regex_match(line, match, DASH_RE)) {
            break;
          }
          else if (std::regex_match(line, match, STEP_RE)) {
            //std::cout << "step?" << line << std::endl;
            goto step_read;
          }
        }

      }

    }
    else {
      exit(1);
    }
  }
finished:
  return;
}


void Renderer::load_trajectory_from_tsv()
{
  // TODO
  // simple format:
  // header line informs number of particles, sim box size
  // next is headings, can garble
  // then is time indicator followed by particle data for every particle
  std::ifstream ifs(this->trajectory_path);
  std::string line, s;
  std::stringstream ss;

  std::getline(ifs, line); // version line
  std::getline(ifs, line); // nL line
  ss.str(line);
  std::cerr << line << std::endl;

  int n=0;
  ss >> s; ss >> n;
  ss >> s; ss >> this->sim_side_length;
  std::cerr << n << ", " << this->sim_side_length << std::endl;

  std::getline(ifs, line); // headings line

  double time=-1.0, x=-1.0, y=-1.0, z=-1.0, diameter=-1.0;

  int istep = 0, id = 0;
  while (std::getline(ifs, line)) {
    ss = std::stringstream(line);
    ss >> s >> time;

    for (int i = 0; i < n; i++) {

      if (!std::getline(ifs, line)) {
        std::cerr << "ERROR: corrupt trajectory." << std::endl;
        exit(1);
      }

      ss = std::stringstream(line);
      //id	mass	inertia	diameter	roughness	positionx	positiony	positionz	orientationx	orientationy	orientationz	velocityx	velocityy	velocityz	angular_velocityx	angular_velocityy	angular_velocityz	forcex	forcey	forcez	positionx	positiony	positionz	kinetic_energy
      ss 
        >> id
        >> s // gobble mass
        >> s // gobble inertia
        >> diameter
        >> s // gobble roughness
        >> x >> y >> z;
      std::cerr << s << std::endl;
      Ogre::Vector3 position(x, y, z);
      ss >> s >> s >> s; // gobble orientation
      ss >> x >> y >> z;
      Ogre::Vector3 velocity(x, y, z);

      if (istep) {
        this->points[id-1].add_timepoint(position, velocity, time);
      }
      else {
        Point p(this, position, velocity, diameter/2.0, this->sim_side_length);
        this->points.push_back(p);
      }

    }

    istep++;
  }

}

void Renderer::load_trajectory()
{
  // TODO
  // load trajectory, guessing file type based on extension
  size_t last_dot_index = this->trajectory_path.rfind(".");
  size_t extension_length = this->trajectory_path.size() - last_dot_index - 1;
  std::string ext = this->trajectory_path.substr(last_dot_index + 1, extension_length);

  if (ext.compare("tsv") == 0) {
    this->load_trajectory_from_tsv();
  }
  else if (ext.compare("yaml") == 0) {
    this->load_trajectory_from_yaml();
  }
  else {
    std::cerr << "Unknown trajectory format: " << ext << ". Valid formats are .tsv and .yaml" << std::endl;
    exit(1);
  }
}
