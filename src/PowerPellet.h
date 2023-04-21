/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include "StaticGameEntity.h"

#include <list>

#include "Timer.h"

template <typename> struct Vector2;

/// <summary>
/// Increases the player's score upon collision with the Avatar and makes Ghosts
/// temporarily vulnerable.
/// </summary>
class PowerPellet : public StaticGameEntity {
 public:
	/// <summary>
	/// Constructor for the PowerPellet class.
	/// </summary>
	/// <param name="position">The tile position of the PowerPellet.</param>
	PowerPellet(Vector2<float> position);
	/// <summary>
	/// 
	/// </summary>
	static bool Draw(const Drawer* drawer, unsigned int elapsed_millis, std::list<PowerPellet*>& power_pellets);

 private:
	/// <summary>
	/// Handles the timing of the blinking visual effect.
	/// </summary>
	static Timer blink_timer_;
	/// <summary>
	/// Determines whether PowerPellets will be drawn.
	/// They are drawn when it is set to true.
	/// </summary>
	static bool draw_;
};