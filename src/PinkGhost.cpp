#include "PinkGhost.h"
#include "Ghost.h"

#include "Vector2.h"

PinkGhost::PinkGhost(Vector2<float> initial_position)
    : Ghost(initial_position, Vector2<char>::down) {}

void PinkGhost::UpdateImage() {
  Ghost::UpdateImage("Pink\\");
}