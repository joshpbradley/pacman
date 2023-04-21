/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <string>

#include "MovableGameEntity.h"
#include "Vector2.h"
#include "Timer.h"

class World;
class GameEntity;

/// <summary>
/// The playable character.
/// </summary>
class Avatar : public MovableGameEntity
{
 public:
	/// <summary>
	// Constructor for the Avatar class.
	/// </summary>
	/// <param name="initial_position">The starting position of the Avatar.</param>
	Avatar(Vector2<float> initial_position);
	/// <summary>
	/// Resets the Avatar.
	/// Called when the player loses a life.
	/// </summary>
	void Reset(void);
	/// <summary>
	/// Updates the Avatar on each frame update..
	/// </summary>
	/// <param name="elapsed_millis">The time elapsed in milliseconds since the previous frame.</param>
	/// <param name="world">Allows the direction for the Avatar to be determined.</param>
	void Update(unsigned int elapsed_millis, const World* world);
	/// <summary>
	/// Changes the player's direction of travel, only if the path in that direction is unblocked.
	/// </summary>
	/// <param name="new_direction">The suggested new direction of travel.</param>
	/// <param name="world">Determines whether the given direction of travel is blocked.</param>
	void set_direction(Vector2<char> new_direction, const World* world);
	/// <summary>
	/// Increments the number of Ghosts caught in a row, returning the result.
	/// </summary>
	/// <returns>The number of Ghosts caught in a row.</returns>
	unsigned char IncrementGhostsCaughtInRow(void);
	/// <summary>
	/// Sets the number of Ghosts caught in a row back to 0.
	/// </summary>
	void ResetGhostsCaughtInRow(void);

 protected:
	/// <summary>
  /// Updates the image that represents the avatar.
  /// Updates Avatar mouth movements and the direction the Avatar is facing. 
  /// </summary>
	void UpdateImage(void) override;

 private:
	/// <summary>
	/// Updates the next_tile_ member to the next tile in the Avatar's current direction if it is not blocking.
	/// Else the Avatar is set to be stationary.
	/// </summary>
	/// <param name="world">Determines whether the next tile can be updated in
	/// the current direction of travel.</param>
	void UpdateNextTile(const World* world);
	/// <summary>
	/// Determines whether the Avatar's mouth should be open or closed.
	/// True if the mouth is open and false if closed.
	/// </summary>
	bool mouth_open_;
	/// <summary>
	/// The timer that maages the opening and closing of the Avatar's mouth.
	/// </summary>
	Timer mouth_timer_;
	/// <summary>
	/// The number of Ghosts caught in a single Power-Pellet use.
	/// </summary>
	unsigned char ghosts_caught_in_row_;
};