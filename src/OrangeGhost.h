#pragma once

#include "Ghost.h"

#include "Vector2.h"

class OrangeGhost : public Ghost {
 public:
  OrangeGhost(Vector2<float> initial_position);
 protected:
  void UpdateImage(void) override;
};