#pragma once

#include "Ghost.h"

#include "Vector2.h"

class CyanGhost : public Ghost {
 public:
  CyanGhost(Vector2<float> initial_position);
 protected:
  void UpdateImage(void) override;
};