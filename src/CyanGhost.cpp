#include "CyanGhost.h"
#include "Ghost.h"

#include "Vector2.h"

CyanGhost::CyanGhost(Vector2<float> initial_position)
  : Ghost(initial_position, Vector2<char>::up) {}

void CyanGhost::UpdateImage() {
  Ghost::UpdateImage("Cyan\\");
}