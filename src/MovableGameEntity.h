/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <string>

#include "GameEntity.h"
#include "Vector2.h"

class World;

/// <summary>
/// Represents an abstract entity in the game that moves.
/// </summary>
class MovableGameEntity : public GameEntity {
 public:
	/// <summary>
	/// Constructor for the MovableGameEntity class.
	/// </summary>
	/// <param name="initial_position">The starting tile position of the entity.</param>
	/// <param name="image_file_path">The path of the entity's image to add to the drawing buffer.</param>
	/// <param name="speed">The speed of the entity.</param>
	MovableGameEntity(Vector2<float> initial_position, float speed, const std::string& image_file_path = "");
	/// <summary>
	/// Resets the position of the entity.
	/// </summary>
	virtual void Reset(void);
	/// <summary>
	/// Gets the current position in tile coordinates.
	/// </summary>
	/// <returns>The current position in tile coordinates.</returns>
	Vector2<unsigned char>GetTilePosition(void) const;
	/// <summary>
	/// Sets the position of the entity to the location represented by the tile.
	/// </summary>
	/// <param name="tile">The coordinates representing the position that the
	/// entity will be set to.</param>
	void SetPositionFromTile(Vector2<unsigned char> tile);
	/// <summary>
	/// Gets the current_tile_ member.
	/// </summary>
	/// <returns>The current_tile_ member.</returns>
	Vector2<unsigned char> current_tile(void) const;
	/// <summary>
	/// Gets whether the current tie is equal to the next tile.
	/// </summary>
	/// <returns>True if the current tile is equal to the next tile, else false.</returns>
	bool CheckIsAtDestination(void) const;

protected:
	/// <summary>
	/// Updates the positioning of the entity.
	/// It ensures that tiles are not skipped as it moves across the map.
	/// </summary>
	/// <param name="elapsed_millis">The amount of time in milliseconds since the previous
	/// frame update.</param>
	void UpdatePosition(unsigned int elapsed_millis);
	/// <summary>
	/// 
	/// </summary>
	virtual void UpdateImage(void) = 0;
	/// <summary>
	/// The start position of the entity in tile coordinates.
	/// </summary>
	const Vector2<float> initial_position_;
	/// <summary>
	///  The movement speed of the entity
	/// </summary>
	float speed_;
	/// <summary>
	///  The tile that the entity is occupying.
	/// </summary>
	Vector2<unsigned char> current_tile_;
	/// <summary>
	/// The tile that the entity is moving towards.
	/// </summary>
	Vector2<unsigned char> next_tile_;
	/// <summary>
	/// The direction the entity is moving in.
	/// </summary>
	Vector2<char> direction_;
	/// <summary>
	/// Determines whether the current image representing the Entity is outdated.
	/// True if the image needs updating, else false.
	/// </summary>
	bool update_image_flag_;
};