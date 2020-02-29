#include "simrenderer.hpp"

void Renderer::animate()
{
  auto scene_manager = this->getRoot()->getSceneManager("mainSceneManager");
  auto anim = scene_manager->createAnimation("anim", 100.0);

  // create tracks for nodes
  unsigned short handles = 0;
  for (auto point: this->point_nodes) {
    auto track = anim->createNodeTrack(handle++);
  }

  // apply
}
