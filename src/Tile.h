/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include "Vector2.h"

/// <summary>
/// A singular tile in the world grid.
/// </summary>
class Tile {
 public:
	 enum class block_type {
		 no_block, partial_block, block
	 };

	/// <summary>
	/// Constructor for the Tile class.
	/// </summary>
	/// <param name="position">The position of the tile in map coordinates.</param>
	/// <param name="block_type">Determines the context in which the tile blocks.
	Tile(Vector2<unsigned char> position, enum block_type block_type);
	/// <summary>
	/// Gets the position of the tile.
	/// </summary>
	/// <returns>The position of the tile.</returns>
	Vector2<unsigned char> position(void) const;
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	block_type block_type(void) const;
	/// <summary>
	/// Determines whether the tile has already been visited in the path generation algorithm.
	/// </summary>
	bool visited_flag_;

 private:
	/// <summary>
	/// The position of the tile in map coordinates.
	/// </summary>
	Vector2<unsigned char> position_;
	/// <summary>
	/// Determines the context of how the tile blocks.
	/// </summary>
	enum block_type block_type_;
};