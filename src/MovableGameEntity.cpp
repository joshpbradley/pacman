/// <author>
/// Joshua Bradley
/// </author>

#include "MovableGameEntity.h"
#include "GameEntity.h"

#include <string>

#include "PacMan.h"
#include "Vector2.h"


MovableGameEntity::MovableGameEntity(Vector2<float> initial_position, float speed,
	const std::string& image_file_path)
		: GameEntity(initial_position, image_file_path),
	    initial_position_(initial_position),
			speed_(speed),
			/*
			 * The casts are to remove errors regarding const-ness and explicitly acknowledging possible loss
			 * of data in conversion.
			 */
			current_tile_(Vector2<unsigned char>(static_cast<unsigned char>(initial_position.x_),
				                                 static_cast<unsigned char>(initial_position.y_))),
			next_tile_(current_tile_),
      update_image_flag_(true) {}

bool MovableGameEntity::CheckIsAtDestination() const {
	return (current_tile_.x_ == next_tile_.x_) && (current_tile_.y_ == next_tile_.y_);
}

Vector2<unsigned char> MovableGameEntity::current_tile() const {
	return current_tile_;
}

void MovableGameEntity::UpdatePosition(unsigned int elapsed_millis) {
	// The location of the entity's destination tile.
	Vector2<float> destination(next_tile_.x_, next_tile_.y_);
	// Converts from the tile position to world position.
	destination *= static_cast<float>(PacMan::kTileSize);

	auto direction = destination - position_;
	auto distanceToMove = elapsed_millis * speed_;

	// True if the distance needed to travel will cause the entity to reach the next tile.
	if (distanceToMove > direction.GetLength()) {
		// Teleports the entity across the map from right to left.
		if (current_tile_ == Vector2<unsigned char>(1, 13)) {
			SetPositionFromTile(Vector2<unsigned char>(27, 13));
			next_tile_ = GetTilePosition();
		// Teleports the entity across the map from left to right.
		} else if (current_tile_ == Vector2<unsigned char>(28, 13)) {
			SetPositionFromTile(Vector2<unsigned char>(2, 13));
			next_tile_ = GetTilePosition();
		// Moves the entity to its destination tile.
		} else {
			set_position(destination);
		}

		current_tile_ = next_tile_;
	}
	// Moves the entity closer to its destination.
	else {
		direction.Normalize();
		position_ += (direction * distanceToMove);
	}
}

void MovableGameEntity::Reset() {
	  // Returns the entity back to its initial position.
	  set_position(initial_position_ * static_cast<float>(PacMan::kTileSize));

		// Sets the current and next tile members to the currently occupied tile. 
		current_tile_ = GetTilePosition();
		next_tile_ = current_tile_;
}

void MovableGameEntity::SetPositionFromTile(Vector2<unsigned char> position) {
	set_position(position * static_cast<float>(PacMan::kTileSize));
}

Vector2<unsigned char> MovableGameEntity::GetTilePosition() const {
	// Converts the current position to the corresponding tile values, as floats.
	Vector2<float> casted_vector(position_.x_ / static_cast<float>(PacMan::kTileSize), position_.y_ / static_cast<float>(PacMan::kTileSize));
	// Casts the floats to unsigned chars.
	return Vector2<unsigned char>(static_cast<unsigned char>(casted_vector.x_), static_cast<unsigned char>(casted_vector.y_));
}