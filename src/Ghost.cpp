/// <author>
/// Joshua Bradley
/// </author>

#include "Ghost.h"
#include "MovableGameEntity.h"
#include "GameEntity.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <array>

#include "Drawer.h"
#include "Tile.h"
#include "World.h"
#include "Vector2.h"

// Ghosts are made vunerable for 8 seconds.
Timer Ghost::vulnerable_timer_ = Timer(8000, false);
// Ghosts invert direction every 5 seconds.
Timer Ghost::invert_timer_ = Timer(5000, true);
// Ghosts invert their wobble state every 150 milliseconds.
Timer Ghost::wobble_timer_ = Timer(150, true);

const float Ghost::kSpeedMultiplier = 3.f;
const float Ghost::kSpeed = .15f;

bool Ghost::vulnerable_flag_ = false;
bool Ghost::invert_direction_flag_ = false;
bool Ghost::wobble_flag_ = false;

Vector2<unsigned char> Ghost::home_tile_;

std::vector<Vector2<unsigned char>> Ghost::path_destinations_ = {};

Ghost::Ghost(Vector2<float> initial_position, Vector2<char> initial_direction)
	: MovableGameEntity(initial_position, kSpeed),
	  initial_direction_(initial_direction),
	  state_(state::healthy),
	  set_path_from_base_flag_(true) {
	direction_ = initial_direction;
}

void Ghost::AddPathDestination(Vector2<unsigned char> tile_position) {
	path_destinations_.push_back(tile_position);
}


Vector2<unsigned char> Ghost::GetRandomPathFromBase() const {
	return path_destinations_[rand() % path_destinations_.size()];
}

void Ghost::SetPathFromBase(World* world) {
	SetPath(world, GetRandomPathFromBase());
}

void Ghost::Die(World* world) {
	state_ = state::dead;

	/*
	 * Sets a path to the Ghosts' home tile.
	 * The Ghost is revived upon reaching this tile.
	 */
	SetPath(world, home_tile_);
	
	speed_ *= kSpeedMultiplier;

	update_image_flag_ = true;
}

void Ghost::Revive(World* world) {
	speed_ /= kSpeedMultiplier;

	update_image_flag_ = true;

	SetPathFromBase(world);

	state_ = state::healthy;
}

void Ghost::PreUpdateHandler(unsigned int elapsed_millis, std::array<Ghost*, 4>& ghosts) {
	if (wobble_timer_.Update(elapsed_millis)) {
		wobble_flag_ = !wobble_flag_;

		for (auto g : ghosts) {
			g->update_image_flag_ = true;
		}
	}

	// Terminates the vulnerability period early if no Ghosts are vulnerable.
	bool vulnerable_remaining = false;
	for (auto g : ghosts) {
		if (g->state_ == state::vulnerable) {
			vulnerable_remaining = true;
			break;
		}
	}

	if (vulnerable_timer_.Update(elapsed_millis) || (vulnerable_flag_ && !vulnerable_remaining)) {
		// Inverts the direction of the Ghosts.
		invert_direction_flag_ = true;
		// Bool to reset vulnerable the individual vulnerable flags.
		vulnerable_flag_ = false;
		// Resumes the inversion of direction.
		invert_timer_.Reset();
		invert_timer_.Resume();
	} else if (invert_timer_.Update(elapsed_millis)) {
		invert_direction_flag_ = true;
	}
}

void Ghost::Update(unsigned int elapsed_millis, World* world) {
	// Ghost invulnerability has ended. 
	if (state_ == state::vulnerable && !vulnerable_flag_) {
		state_ = state::healthy;
		update_image_flag_ = true;
	}
	
	// Ghost inverts its direction.
	if (invert_direction_flag_ && path_.empty() && state_ != state::dead) {
		direction_ *= -1.f;

		auto temp_tile = current_tile_;
		current_tile_ = next_tile_;
		next_tile_ = temp_tile;
	}

	// The Ghost is currently placed on a tile.
	if (CheckIsAtDestination()) {
		// If the Ghost has not completed its designated path, continue along it.
		if (!path_.empty()) {
			Tile* next_tile = path_.front();
			path_.pop_front();
			next_tile_ = next_tile->position();

			direction_ = {
			  next_tile_.x_ - current_tile_.x_,
				next_tile_.y_ - current_tile_.y_,
			};
			// Revive if the ghost is in a dead state and has reached its home tile.
		} else if (state_ == state::dead && current_tile_ == home_tile_) {
			Revive(world);
			// Set a path out of the base if the set_path_from_base_ flag is set.
		} else if (set_path_from_base_flag_) {
			set_path_from_base_flag_ = false;
			SetPathFromBase(world);
			// Force the Ghost to move in a specific direction if it is valid, or relative to that direction if it is not.
		} else {
			direction_ = GenerateRandomDirection(direction_, world);
			next_tile_ = World::GetTileInDirection(current_tile_, direction_);
		}
	}

	UpdatePosition(elapsed_millis);
	UpdateImage();
}

void Ghost::PostUpdateHandler() {
	if (invert_direction_flag_) {
		invert_direction_flag_ = false;
	}
}

void Ghost::HandleVulnerableEvent(std::array<Ghost*, 4>& ghosts) {
	invert_direction_flag_ = true;
	vulnerable_flag_ = true;

	vulnerable_timer_.Reset();
	vulnerable_timer_.Resume();

 /*
	* Prevents the Ghosts' directions to invert (as a result of the inversion timer reaching zero) for the
	* duration of the vulnerability period.
	*/
	invert_timer_.Pause();

	for (auto g : ghosts) {
		g->HandleVulnerableEvent();
	}
}

void Ghost::HandleVulnerableEvent() {
	if (state_ != state::dead) {
		state_ = state::vulnerable;
		update_image_flag_ = true;
	}
}

void Ghost::Reset(World* world, std::array<Ghost*, 4>& ghosts) {
 /*
	* Resets the timers and associated flags that are class-level members.
	* 
	* Note: the vulnerability timer is not reset here; that is because
	* it is automatically reset upon consuming a power pellet.
	*/
	invert_timer_.Reset();
	wobble_timer_.Reset();

	wobble_flag_ = false;
	invert_direction_flag_ = false;
	vulnerable_flag_ = false;

	// Reset instance-level state.
	for (auto& g : ghosts) {
		g->Reset(world);
	}
}

void Ghost::Reset(World* world) {
	MovableGameEntity::Reset();

	state_ = state::healthy;
	speed_ = kSpeed;
	direction_ = initial_direction_;

	set_path_from_base_flag_ = true;
	update_image_flag_ = true;

	UpdateImage();
}

void Ghost::Update(unsigned int elapsed_millis, World* world, std::array<Ghost*, 4>& ghosts) {
	// Handles the static Ghost data post-update.
	PreUpdateHandler(elapsed_millis, ghosts);

	// Updates the individual Ghost instances.
	for (auto g : ghosts) {
		g->Update(elapsed_millis, world);
	}

	// Handles the static Ghost data post-update.
	PostUpdateHandler();
}

void Ghost::UpdateImage(std::string colour_path) {
	if (update_image_flag_) {
		update_image_flag_ = false;

		std::stringstream path;

		path << "Ghosts\\";

		// Sets the dead section of the path: for dead Ghosts.
		if (state_ == state::dead) {
			path << "Dead";
		} else {
			// Sets the vulnerable section of the path: for vulnerable Ghosts.
			if (state_ == state::vulnerable) {
				path << "Vulnerable\\";
			} else {
				// Sets the colour section of the path: for Ghosts that are neither dead nor vulnerable.
				path << colour_path;

				if (direction_ == Vector2<char>::up) {
					path << "Up_";
				} else if (direction_ == Vector2<char>::down) {
					path << "Down_";
				} else if (direction_ == Vector2<char>::left) {
					path << "Left_";
				} else {
					path << "Right_";
				}
			}

			// Sets wobble section of path: for Ghosts that aren't dead.
			path << (wobble_flag_ ? "Wobble_0" : "Wobble_1");
		}

		path << ".png";

		set_image_file_path(path.str());
	}
}

void Ghost::SetPath(World* world, Vector2<unsigned char> destination) {
	path_.clear();
	world->GetPath(current_tile_, destination, path_);
}

enum Ghost::state Ghost::state() const {
	return state_;
}

Vector2<char> Ghost::GenerateRandomDirection(Vector2<char> reference_direction, World* world) {
	Vector2<char> lateral_direction = {reference_direction.y_, reference_direction.x_};
	Vector2<char> other_lateral_direction = {reference_direction.y_ * -1, reference_direction.x_ * -1};
	std::vector<Vector2<char>> possible_directions;
	std::vector<Vector2<char>> valid_directions;

	// The possible movements, not yet validated.
	possible_directions.push_back(reference_direction);
	possible_directions.push_back(lateral_direction);
	possible_directions.push_back(other_lateral_direction);

	// The directions from the possible directions that are valid.
	for (auto& v : possible_directions) {
		if (world->CheckTileValidity(Vector2<unsigned char>(current_tile_.x_ + v.x_, current_tile_.y_ + v.y_), Tile::block_type::no_block)) {
			valid_directions.push_back(v);
		}
	}

	return valid_directions.empty() ? reference_direction *= -1 : valid_directions[rand() % valid_directions.size()];
}

void Ghost::set_home_tile(Vector2<unsigned char> tile_position) {
	home_tile_ = tile_position;
}