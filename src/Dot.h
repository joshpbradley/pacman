/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include  "StaticGameEntity.h"

template <typename> struct Vector2;

/// <summary>
/// A small circular dot that increases the player's score upon collision with the Avatar,
/// and is subsequently removed. The player wins the game when all Dots have been removed.
/// </summary>
class Dot : public StaticGameEntity {
 public:
	/// <summary>
	/// Constructor for the Dot class.
	/// </summary>
	/// <param name="position">The tile position of the Dot.</param>
	Dot(Vector2<float> position);
};