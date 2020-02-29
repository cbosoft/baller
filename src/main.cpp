#include "simrenderer.hpp"

int main(void) //int argc, char **argv)
{
  try
  {
  	Renderer app(1000, 0.01, 10.0, 10.0);
    app.initApp();
    //app.readTrajectory(); // TODO
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
