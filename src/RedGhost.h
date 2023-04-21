#pragma once

#include "Ghost.h"

#include <vector>

#include "Vector2.h"

class RedGhost : public Ghost {
 public:
  RedGhost(Vector2<float> initial_position);
  static void AddPathDestination(Vector2<unsigned char> tile_position);

 protected:
  void UpdateImage(void) override;

 private:
  /// <summary>
  /// Holds all of the destinations in the map that the Ghosts can follow upon reset and game start.
  /// </summary>
  static std::vector<Vector2<unsigned char>> path_destinations_;
  Vector2<unsigned char> GetRandomPathFromBase() const override;
};