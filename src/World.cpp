/// <author>
/// Joshua Bradley
/// </author>

#include "World.h"

#include <fstream>
#include <sstream>
#include <list>

#include "ResourceManager.h"
#include "RedGhost.h"
#include "Ghost.h"
#include "Tile.h"
#include "Dot.h"
#include "PowerPellet.h"
#include "Vector2.h"
#include "Drawer.h"
#include "StaticGameEntity.h"
#include "GameEntity.h"

World::World()
	: map_structure_file_path_("Map\\Structure.txt"),
	  map_image_file_path_("Map\\Map.png") {}

void World::Init() {
	std::string line;
	std::ifstream map_file(ResourceManager::kAssetPath + map_structure_file_path_);

	// Handle file not accessible error.
	if (map_file.fail()) {
		throw std::ios_base::failure("Cannot find/access \"" + ResourceManager::kAssetPath + map_structure_file_path_ + "\"");
	} else if (map_file.is_open()) {
		unsigned char line_index = 0;

		while (!map_file.eof()) {
			std::getline(map_file, line);

			for (unsigned char i = 0; i < line.length(); i++) {
				// Create tiles - signalling whether a tile acts as a wall.
				Tile* tile;

				switch (line[i]) {
					case 'x': {
						tile = new Tile({i, line_index}, Tile::block_type::block);
						break;
					}
					case '-': {
						tile = new Tile({i, line_index}, Tile::block_type::partial_block);
						break;
					}
					default: {
						tile = new Tile({i, line_index}, Tile::block_type::no_block);
					}
				}

				switch (line[i]) {
					// Initialise Dot.
					case '.': {
						auto dot = new Dot(Vector2<float>(i, line_index));
						dots_.push_back(dot);
						break;
					}
					// Initialise Power Pellet.
					case 'o': {
						auto power_pellet = new PowerPellet(Vector2<float>(i, line_index));
						power_pellets_.push_back(power_pellet);
						break;
					}
					// Initialise Ghost home tile.
					case 'H': {
						Ghost::set_home_tile(Vector2<unsigned char>(i, line_index));
						break;
					}
					case 'R': {
						RedGhost::AddPathDestination(Vector2<unsigned char>(i, line_index));
					}
					case 'P': {
						Ghost::AddPathDestination(Vector2<unsigned char>(i, line_index));
						break;
					}
				}

				tiles_.push_back(tile);
			}

			line_index++;
		}
		map_file.close();
	}
}

void World::Draw(const Drawer* drawer, unsigned int elapsed_millis) {
	drawer->Draw(map_image_file_path_, Vector2<float>::zero);

	for (auto dot : dots_) {
		dot->Draw(drawer);
	}

	PowerPellet::Draw(drawer, elapsed_millis, power_pellets_);
}

bool World::CheckTileValidity(Vector2<unsigned char> potential_tile, enum Tile::block_type max_valid_block_type) const {
	for (auto tile : tiles_) {
		if (potential_tile == tile->position() && tile->block_type() <= max_valid_block_type) {
			return true;
		}
	}

	return false;
}

bool World::CheckDotIntersection(Vector2<float> position) {
	for (auto dot : dots_) {
		if ((dot->position() - position).GetLength() < 5.f) {
			dots_.remove(dot);
			delete dot;
			return true;
		}
	}

	return false;
}

bool World::CheckPowerPelletIntersection(Vector2<float> position) {
	for (auto power_pellet : power_pellets_) {
		if ((power_pellet->position() - position).GetLength() < 5.f) {
			power_pellets_.remove(power_pellet);
			delete power_pellet;
			return true;
		}
	}

	return false;
}

void World::GetPath(Vector2<unsigned char> from_tile_position, Vector2<unsigned char> to_tile_position, std::list<Tile*>& list) {
	Tile* from_tile = GetTileAtPosition(from_tile_position);
	Tile* to_tile = GetTileAtPosition(to_tile_position);

	for (auto tile : tiles_) {
		tile->visited_flag_ = false;
	}

	GeneratePath(from_tile, to_tile, list);
}

Tile* World::GetTileAtPosition(Vector2<unsigned char> tile_position) {
	for (auto tile : tiles_) {
		if (tile_position == tile->position()) {
			return tile;
		}
	}

	return NULL;
}

bool World::GeneratePath(Tile* from_tile, const Tile* to_tile, std::list<Tile*>& path) {
	from_tile->visited_flag_ = true;

	// The path has been completed.
	if (from_tile == to_tile) {
		return true;
	}

	std::list<Tile*> neighbors;

	/*
	 * Retrieves the tiles to the immediate up, down, left and right of the current tile, that are eligible
	 * to become the next tile in the path.
	 */
	Tile* up = GetTileAtPosition(GetTileInDirection(from_tile->position(), Vector2<char>::up));
	if (up && !up->visited_flag_ && up->block_type() != Tile::block_type::block) {
		neighbors.push_back(up);
	}

	Tile* down = GetTileAtPosition(GetTileInDirection(from_tile->position(), Vector2<char>::down));
	if (down && !down->visited_flag_ && down->block_type() != Tile::block_type::block) {
		neighbors.push_back(down);
	}

	Tile* right = GetTileAtPosition(GetTileInDirection(from_tile->position(), Vector2<char>::right));
	if (right && !right->visited_flag_ && right->block_type() != Tile::block_type::block) {
		neighbors.push_back(right);
	}

	Tile* left = GetTileAtPosition(GetTileInDirection(from_tile->position(), Vector2<char>::left));
	if (left && !left->visited_flag_ && left->block_type() != Tile::block_type::block) {
		neighbors.push_back(left);
	}

	// Sorts the tiles in order of closest to furthest away from the destination tile.
	neighbors.sort([to_tile](Tile* a, Tile* b) {
		short a_x = a->position().x_;
		short a_y = a->position().y_;
		short b_x = b->position().x_;
		short b_y = b->position().y_;
		short dest_x = to_tile->position().x_;
		short dest_y = to_tile->position().y_;

		int la = abs(a_x - dest_x) + abs(a_y - dest_y);
		int lb = abs(b_x - dest_x) + abs(b_y - dest_y);

		return la < lb;
	});

 /*
	* Paths are generated by adding the eligible tile closest to the destination, then recursively calling this function.
	* If a potential path fails (no eligible tiles to add to the path) then the last tile added to the path is removed,
	* and a path is attempted using the second-closest tile to the destination.
	* 
	* This algorithm is a heuristic, with solutions guaranteeing all tiles are valid and tiles are not repeated in the path.
	*/
	for (auto tile : neighbors) {
		path.push_back(tile);

		// If true, the path has reached the destination. Returns from all recursive calls of the function and exits.
		if (GeneratePath(tile, to_tile, path)) {
			return true;
		}

		/*
		 * A path could not be generated for the current neighbour, so revert to the current tile and query the
		 * next-closest tile.
		 */
		path.pop_back();
	}

	// The current tile cannot be part of the path because all neighbours are invalid.
	return false;
}

bool World::CheckDotsRemaining() {
	return !dots_.empty();
}

Vector2<unsigned char> World::GetTileInDirection(Vector2<unsigned char> tile, Vector2<char> direction) {
	return Vector2<unsigned char>(tile.x_ + direction.x_, tile.y_ + direction.y_);
}