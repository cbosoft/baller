#include <fstream>
#include <iomanip>

#include "simrenderer.hpp"
#include "point.hpp"

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

  int n=0, aid=-1, bid=-1;
  ss >> s; ss >> n;
  ss >> s; ss >> this->sim_side_length;
  std::cerr << n << ", " << this->sim_side_length << std::endl;

  std::getline(ifs, line); // headings line

  double time=-1.0, x=-1.0, y=-1.0, z=-1.0, diameter=-1.0;

  int istep = 0, id = 0;
  while (std::getline(ifs, line)) {
    ss = std::stringstream(line);
    ss >> s >> time >> aid >> s >> bid;
    this->interacting_ids.push_back(std::make_pair(aid, bid));
    this->times.push_back(time);

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
      Ogre::Vector3 position(x, y, z);
      ss >> s >> s >> s; // gobble orientation
      ss >> x >> y >> z;
      Ogre::Vector3 velocity(x, y, z);

      if (istep) {
        this->points[id-1].add_timepoint(position, velocity);
      }
      else {
        Point p(this, position, velocity, diameter/2.0, id);
        this->points.push_back(p);
      }

    }

    istep++;
  }

}

void Renderer::load_trajectory()
{
  // load trajectory, guessing file type based on extension
  size_t last_dot_index = this->trajectory_path.rfind(".");
  size_t extension_length = this->trajectory_path.size() - last_dot_index - 1;
  std::string ext = this->trajectory_path.substr(last_dot_index + 1, extension_length);

  if (ext.compare("tsv") == 0) {
    this->load_trajectory_from_tsv();
  }
  else {
    std::cerr << "Unknown trajectory format: " << ext << ". Valid format is .tsv." << std::endl;
    exit(1);
  }
}
