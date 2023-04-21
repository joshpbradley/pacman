#pragma once

#include <string>

#include "Ghost.h"
#include "Vector2.h"

struct GhostImageData;
template <typename T> struct Vector2;

class GhostImageHandler {
  struct GhostImageData {
    GhostImageHandler::Colour colour_;
    bool dead_flag_;
    bool vunerable_flag_;
    Vector2<char> direction;
  };

 public:
   /// <summary>
   /// The Ghost's colour.
   /// </summary>
   enum Colour {
     RED, CYAN, PINK, ORANGE
   };

  static void DecreaseTimers(unsigned int elapsed_millis);
  static std::string GenerateImagePath(const GhostImageData &gid);

 private:
   static int wobble_timer_;
   static bool wobble_;
};