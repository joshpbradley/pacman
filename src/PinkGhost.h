#pragma once

#include "Ghost.h"

#include "Vector2.h"

class PinkGhost : public Ghost {
 public:
  PinkGhost(Vector2<float> initial_position);
 protected:
  void UpdateImage(void) override;
};