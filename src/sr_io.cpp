#include <fstream>
#include <regex>

#include "simrenderer.hpp"
#include "point.hpp"

const std::regex STEP_RE("^ - step:$");
const std::regex TIME_RE("^   time: ([\\d.\\-e+]*)$");
const std::regex DASH_RE("^      - ?$");
const std::regex   ID_RE("^        id: (\\d*)$");
const std::regex MASS_RE("^        mass: (\\d*)$");
const std::regex DIAM_RE("^        diameter: (\\d*)$");
const std::regex  POS_RE("^        position: \\[([\\d.\\-e+]*), ([\\d.\\-e+]*), ([\\d.\\-e+]*)\\]$");

void Renderer::load_trajectory()
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
  float time = 0.0, x = 0.0, y = 0.0, z = 0.0, diameter = 0.0;
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
          x = atof(match.str(1).c_str());
          y = atof(match.str(2).c_str());
          z = atof(match.str(3).c_str());
          //std::cerr << x << ", " << y << ", " << z << std::endl;
        }

        if (step) {
          this->points[id-1].add_timepoint({x, y, z}, time);
        }
        else {
          Point p(this, {x, y, z}, diameter/2.0);
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
