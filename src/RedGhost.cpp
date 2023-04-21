#include "RedGhost.h"
#include "Ghost.h"

#include "Vector2.h"

std::vector<Vector2<unsigned char>> RedGhost::path_destinations_ = {};

RedGhost::RedGhost(Vector2<float> initial_position)
    : Ghost(initial_position, Vector2<char>::left) {}

void RedGhost::UpdateImage() {
  Ghost::UpdateImage("Red\\");
}

void RedGhost::AddPathDestination(Vector2<unsigned char> tile_position) {
  path_destinations_.push_back(tile_position);
}

Vector2<unsigned char> RedGhost::GetRandomPathFromBase() const {
  return path_destinations_.at(rand() % path_destinations_.size());
}