/// <author>
/// Joshua Bradley
/// </author>

#include "Tile.h"

#include "Vector2.h"

Tile::Tile(Vector2<unsigned char> position, enum block_type block_type)
    : position_(position),
      block_type_(block_type),
      visited_flag_(false) {}

Vector2<unsigned char> Tile::position() const {
  return position_;
}

enum Tile::block_type Tile::block_type() const {
  return block_type_;
}