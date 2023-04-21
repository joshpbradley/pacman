#include "OrangeGhost.h"
#include "Ghost.h"

#include "Vector2.h"

OrangeGhost::OrangeGhost(Vector2<float> initial_position)
  : Ghost(initial_position, Vector2<char>::up) {}

void OrangeGhost::UpdateImage() {
  Ghost::UpdateImage("Orange\\");
}