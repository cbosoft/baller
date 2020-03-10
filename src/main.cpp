#include "simrenderer.hpp"
#include "textrenderer.hpp"

int main(int argc, char **argv)
{
  std::string trajectory = "traj.yaml";
  argc --; argv++;
  if (argc > 0) {
    trajectory = argv[0];
  }

  try
  {
  	Renderer app(trajectory, 10, 10.0, 1.0);
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error occurred during execution: " << e.what() << '\n';
    return 1;
  }

  return 0;
}

//! [fullsource]
