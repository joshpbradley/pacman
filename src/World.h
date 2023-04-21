/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <list>
#include <string>

#include "Tile.h"

template <typename T> struct Vector2;
class Drawer;
class PowerPellet;
class Dot;

/// <summary>
/// Responsible for handling map generation, testing tile validity for GameEntity movement
/// and generating paths for Ghosts.
/// </summary>
class World {
 public:
	/// <summary>
	/// Constructor for the World class.
	/// </summary>
	World::World(void);
	/// <summary>
	/// Initialises the map's walls and creates static GameEntities.
	/// </summary>
	void Init(void);
	static Vector2<unsigned char> GetTileInDirection(Vector2<unsigned char> tile, Vector2<char> direction);
	/// <summary>
	/// Handles the addition of World images to the drawing buffer.
	/// Includes the map image and StaticEntities.
	/// </summary>
	/// <param name="drawer">Adds the images to the drawing buffer.</param>
	/// <param name="elapsed_millis">The amount of time in milliseconds since the previous
	/// frame update.</param>
	void Draw(const Drawer* drawer, unsigned int elapsed_millis);
	/// <summary>
	/// Determines whether the supplied tile is a blocking tile.
	/// </summary>
	/// <param name="tile_position">The position of the tile to inspect in map coordinates.</param>
	/// <param name="max_valid_block_type">The most blocking tile type that is still considered valid in the given context.</param>
	/// <returns>True if a tile is not a blocking tile, else false.</returns>
	bool CheckTileValidity(Vector2<unsigned char> tile_position, enum Tile::block_type max_valid_block_type) const;
	/// <summary>
	/// Determines whether a Dot is located at the given position.
	/// Used to determine whether the Avatar has collected a Dot.
	/// </summary>
	/// <param name="position">The posiiton to search for a Dot.</param>
	/// <returns>True if a Dot is present at the location, else false.</returns>
	bool CheckDotIntersection(Vector2<float> position);
	/// <summary>
	/// Determines whether a PowerPellet is located at the given position.
	/// Used to determine whether the Avatar has collected a PowerPellet.
	/// </summary>
	/// <param name="position">The posiiton to search for a PowerPellet.</param>
	/// <returns>True if a Dot is present at the location, else false.</returns>
	bool CheckPowerPelletIntersection(Vector2<float> position);
	/// <summary>
	/// Wrapper function that generates a path from from_tile to to_tile,
	/// storing the result in the given list.
	/// </summary>
	/// <param name="from_tile_coordinates">The coordinates of the starting tile of the path.</param>
	/// <param name="to_tile_coordinates">The coordinates of the destination tile of the path.</param>
	/// <param name="list">The list that the path is inserted into.</param>
	void GetPath(Vector2<unsigned char> from_tile_coordinates, Vector2<unsigned char> to_tile_coordinates,
		std::list<Tile*>& list);
	/// <summary>
	/// Determines whether Dots are present in the game.
	/// </summary>
	/// <returns>True if at least one Dot exists on the map, else false.</returns>
	bool CheckDotsRemaining(void);

 private:
	/// <summary>
	/// Gets the tile located at the map coordinate tile_position.
	/// </summary>
	/// <param name="tile_position">The map coordinates of the desired tile.</param>
	/// <returns>The tile instance at the specified position.</returns>
	Tile* GetTileAtPosition(Vector2<unsigned char> tile_position);
	/// <summary>
	/// Recursively generates a path from from_tile to to_tile, storing the result in the supplied list.
	/// Heuristic depth-first traversal algorithm.
	/// </summary>
	/// <param name="from_tile">The source tile for the path.</param>
	/// <param name="to_tile">The destination tile for the path.</param>
	/// <param name="path">The generated path.</param>
	/// <returns>True if from_tile is equal to to_tile, else false.</returns>
	bool GeneratePath(Tile* from_tile, const Tile* to_tile, std::list<Tile*>& path);
	/// <summary>
	/// The path of the file that stores the map's structure.
	/// </summary>
	std::string map_structure_file_path_;
	/// <summary>
	/// The path of the file that stores the map's image.
	/// </summary>
	std::string map_image_file_path_;
	/// <summary>
	/// The collection of tiles that compose the map.
	/// </summary>
	std::list<Tile*> tiles_;
	/// <summary>
	/// The collection of Dot entities in the world.
	/// </summary>
	std::list<Dot*> dots_;
	/// <summary>
	/// The collection of PowerPellet entities in the world.
	/// </summary>
	std::list<PowerPellet*> power_pellets_;
};