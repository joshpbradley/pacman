#include "GhostImageHandler.h"

#include <sstream>

#include "Vector2.h"
#include "GhostImageData.h"

GhostImageHandler::wobble_timer_ = 200;
GhostImageHandler::wobble_ = false;

std::string GhostImageHandler::GenerateImagePath(const GhostImageData &gid) {
  std::stringstream result;

  result << "Ghosts\\";

  if (gid.dead_) {
    result << "Dead";
  }
  else {
    if (gid.vulnerable_) {
      result << "Vulnerable\\";
    } else {
      switch (gid.colour_) {
        case Ghost::Colour::RED: {
          result << "Red\\";
          break;
        }
        case Ghost::Colour::CYAN: {
          result << "Cyan\\";
          break;
        }
        case Ghost::Colour::PINK: {
          result << "Pink\\";
          break;
        }
        case Ghost::Colour::ORANGE: {
          result << "Orange\\";
          break;
        }
      }
    }

    result << wobble_ ? "Wobble0" : "Wobble1";
  }

  result << ".png";

  return result.str();
}

void GhostImageHandler::DecreaseTimers(unsigned int elapsed_millis) {
  if ((wobble_timer_ -= elapsed_millis) < 0) {
    wobble = !wobble;
    wobble_timer_ = 200;
  }
}