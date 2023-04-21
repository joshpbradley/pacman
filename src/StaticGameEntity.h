/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include "GameEntity.h"

#include <string>

template <typename> struct Vector2;

/// <summary>
/// Represents an abstract entity in the game that does not move.
/// </summary>
class StaticGameEntity : public GameEntity {
 public:
	/// <summary>
	/// Constructor for the StaticGameEntity class.
	/// </summary>
	/// <param name="position">The tile position of the entity.</param>
	/// <param name="image_file_path">The path of the entity's image to add to the drawing buffer.</param>
	StaticGameEntity(Vector2<float> position, const std::string& image_file_path = "");
};