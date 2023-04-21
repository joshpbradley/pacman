/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <list>
#include <vector>
#include <string>

#include "MovableGameEntity.h"
#include "Vector2.h"
#include "Timer.h"

class Drawer;
class MovableGameEntity;
class World;
class Tile;

/// <summary>
/// Adversaries that can reduce the player's lives if they contact the Avatar,
/// but can also be a source of points if contacted while they are vulnerable.
/// </summary>
class Ghost : public MovableGameEntity {
public:
	/// <summary>
	/// The states of the Ghost.
	/// 
	/// healthy is the default Ghost state - if the Avatar makes contact wuth a Ghost in this state, a life is lost.
	/// vulnerable means the Ghost can be killed if contact is made with the Avatar.
	/// dead means the Ghost is dead, and is travelling back to the home bease where it is revived.
	/// </summary>
	enum class state {healthy, vulnerable, dead};
	/// <summary>
	/// Constructor for the Ghost class.
	/// </summary>
	/// <param name="initial_position">The starting tile position of the Ghost.</param>
	/// <param name="initial_direction">The starting direction of the Ghost.</param>
	Ghost(Vector2<float> initial_position, Vector2<char> initial_direction);
	/// <summary>
	/// Updates all Ghosts in the supplied array.
	/// </summary>
	/// <param name="elapsed_millis">The number of milliseconds since the last frame update.</param>
	/// <param name="world">Determines the tile validity for Ghost movement.</param>
	/// <param name="ghosts">The collection of Ghosts to update.</param>
	static void Update(unsigned int elapsed_millis, World* world, std::array<Ghost*, 4>& ghosts);
	/// <summary>
	/// Resets all Ghosts in the supplied array.
	/// </summary>
	/// <param name="world">Sets the paths of the Ghosts.</param>
	/// <param name="ghosts"The collection of Ghosts to reset.></param>
	static void Reset(World* world, std::array<Ghost*, 4>& ghosts);
	/// <summary>
	/// Handles the event causing Ghosts to become vulnerable, for all the Ghosts in the supplied array.
	/// </summary>
	static void HandleVulnerableEvent(std::array<Ghost*, 4>& ghosts);
	/// <summary>
	/// Sets the position of the home tile. Ghosts will be redirected here upon death.
	/// </summary>
	/// <param name="home_position">The position of the Ghosts' home tile.</param>
	static void set_home_tile(Vector2<unsigned char> home_position);
	/// <summary>
	/// Sets the initial path for the Ghost out of the base.
	/// </summary>
	/// <param name="world">Sets the path for the Ghost back to the home tile.</param>
	void SetPathFromBase(World* world);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="tile_position"></param>
	static void AddPathDestination(Vector2<unsigned char> tile_position);
	/// <summary>
	/// Kills a Ghost. A Ghost dies when it is contacted by the Avatar when it is vulnerable.
	/// </summary>
	/// <param name="world">Sets the path for the Ghost back to the home tile.</param>
	void Die(World* world);
	/// <summary>
	/// Gets the state of the Ghost.
	/// </summary>
	/// <returns>The state of the Ghost.</returns>
	enum state state(void) const;

 protected:
	/// <summary>
	/// Sets a new path for the Ghost to follow to a given destination.
	/// </summary>
	/// <param name="world">Sets the path.</param>
	/// <param name="destination">The location of the destination tile.</param>
	void SetPath(World* world, Vector2<unsigned char> destination);
	/// <summary>
	/// Generates a random direction relative to the reference direction. The returned direction will be the direction itself
	/// or the direction to the left or right of it, if any of these are valid. Else, it will return the only direction remaining -
	/// the direction pointing iin the reverse direction.
	/// </summary>
	/// <param name="reference_direction">The direction that candidate directions are relative to.</param>
	/// <param name="world">Determines whether the directions are valid for the Ghost to travel in.</param>
	/// <returns>A direction relative to the reference direction.</returns>
	Vector2<char> GenerateRandomDirection(Vector2<char> reference_direction, World* world);
	/// <summary>
	/// Handles the reset of a Ghost upon losing a life.
	/// </summary>
	/// <param name="world">Sets the path to exit the base.</param>
	virtual void Reset(World* world);
	/// <summary>
	/// Updates the state of the Ghost upon a frame update.
	/// </summary>
	/// <param name="elapsed_millis">The time in milliseconds since the previous frame update.</param>
	/// <param name="world">Determines which tiles are valid for the Ghost to move to.</param>
	virtual void Update(unsigned int elapsed_millis, World* world);
	/// <summary>
	/// Updates the image that represents the Ghost.
	/// Updates Ghost wobble movements and the direction the Ghost is facing.
	/// Also updates the image for the vulnerable and dead Ghost states.
	/// </summary>
	virtual void UpdateImage(void) = 0;
	/// <summary>
	/// Updates the image that represents the Ghost.
	/// Updates Ghost wobble movements and the direction the Ghost is facing.
	/// Also updates the image for the vulnerable and dead Ghost states.
	/// </summary>
	/// <param name="colour_path">The portion of the file path relating to the Ghost's colour.</param>
	void UpdateImage(std::string colour_path);

	virtual Vector2<unsigned char> GetRandomPathFromBase(void) const;
	/// <summary>
	/// The path that the Ghost must travel.
	/// </summary>
	std::list<Tile*> path_;
	/// <summary>
	/// The direction that the Ghost travels in at the start of the game and on resets.
	/// </summary>
	Vector2<char> initial_direction_;

 private:
	/// <summary>
	/// Handles the static data associated with Ghosts before each update.
	/// </summary>
	/// <param name="elapsed_millis">The elapsed number of milliseconds since the previous frame update.</param>
	/// <param name="ghosts">The Ghosts that must be processed to handle pre-update handling.</param>
	static void PreUpdateHandler(unsigned int elapsed_millis, std::array<Ghost*, 4>& ghosts);
	/// <summary>
	/// Handles the static data associated with Ghosts after each update.
	/// </summary>
	static void PostUpdateHandler(void);
	/// <summary>
	/// Resets the Ghosts state after a Ghost has ended its vulnerable state.
	/// </summary>
	void HandleVulnerableEvent(void);
	/// <summary>
	/// Indicates that the Ghost should not be considered dead, and sets the path to exit the base.
	/// </summary>
	/// <param name="world">Sets the path to exit the base.</param>
	void Revive(World* world);
	/// <summary>
	/// The default speed of the Ghost.
	/// </summary>
	static const float kSpeed;
	/// <summary>
	/// The amount that speed is scaled by while the Ghost is in the 'dead' state.
	/// </summary>
	static const float kSpeedMultiplier;
	/// <summary>
	/// The tile position that Ghosts must reach in order to revive.
	/// </summary>
	static Vector2<unsigned char> home_tile_;
	/// <summary>
	/// Manages the timing of the Ghost vulnerabilty period.
	/// </summary>
	static Timer vulnerable_timer_;
	/// <summary>
	/// Manages the timing of the Ghost direction inversion.
	/// </summary>
	static Timer invert_timer_;
	/// <summary>
	/// Manages the timing of the Ghost sprite flipping between two variants, simulating a 'wobble' effect.
	/// </summary>
	static Timer wobble_timer_;
	/// <summary>
	/// Inverts the direction of all Ghosts that are not following a path when set to true.
	/// Direction inverts when this is set to true.
	/// </summary>
	static bool invert_direction_flag_;
	/// <summary>
	/// Manages the vulnerability state for Ghosts. Corresponds with the timer that tracks vulnerability.
	/// </summary>
	static bool vulnerable_flag_;
	/// <summary>
	/// Manages the appearance of the sprite, allowing it to flip between two different images.
	/// </summary>
	static bool wobble_flag_;
	/// <summary>
	/// The state of the Ghost.
	/// </summary>
	enum state state_;
	/// <summary>
	/// Signals that the Ghost should exit the base.
	/// </summary>
	bool set_path_from_base_flag_;
	/// <summary>
	/// Holds all of the destinations in the map that the Ghosts can follow upon reset and game start.
	/// </summary>
	static std::vector<Vector2<unsigned char>> path_destinations_;
};