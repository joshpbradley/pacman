/// <author>
/// Joshua Bradley
/// </author>

#include "Avatar.h"
#include "MovableGameEntity.h"

#include <sstream>

#include "Timer.h"
#include "Vector2.h"
#include "World.h"
#include "Tile.h"

Avatar::Avatar(Vector2<float> initial_position)
	: MovableGameEntity(initial_position, .25f),
	  mouth_open_(false),
	  ghosts_caught_in_row_(0),
	  mouth_timer_(Timer(80, true)) {
	direction_ = Vector2<char>::left;
}


void Avatar::Update(unsigned int elapsed_millis, const World* world) {
	// Updates position if the Avatar is not stationary.
	if (direction_ != Vector2<char>::zero) {
		UpdatePosition(elapsed_millis);
		mouth_timer_.Resume();
	} else {
		mouth_timer_.Pause();
	}

	UpdateNextTile(world);

	if (mouth_timer_.Update(elapsed_millis)) {
		update_image_flag_ = true;
		mouth_open_ = !mouth_open_;
	}

	UpdateImage();
}

void Avatar::UpdateImage() {
	if (update_image_flag_) {
		update_image_flag_ = false;

		std::stringstream result;

		result << "Avatar\\";

		if (!mouth_open_ || direction_ == Vector2<char>::zero) {
			result << "Closed";
		}
		else {
			result << "Open-";


			if (direction_ == Vector2<char>::up) {
				result << "Up";
			} else if (direction_ == Vector2<char>::down) {
				result << "Down";
			} else if (direction_ == Vector2<char>::left) {
				result << "Left";
			} else if (direction_ == Vector2<char>::right) {
				result << "Right";
			}
		}
		result << ".png";

		set_image_file_path(result.str());
	}
}

void Avatar::UpdateNextTile(const World* world) {
	if (CheckIsAtDestination()) {
		Vector2<unsigned char> next_tile = World::GetTileInDirection(current_tile_, direction_);

		// Continues movement in current direction if unblocked, else the Avatar is set to stationary.
		if (world->CheckTileValidity(next_tile, Tile::block_type::no_block)) {
			next_tile_ = next_tile;
		} else {
			direction_ = Vector2<char>::zero;
		}
	}
}

void Avatar::set_direction(Vector2<char> new_direction, const World* world) {
	// Prevents update if it's in current direction of travel.
	if (direction_ != new_direction) {
		// Prevents direction update if the path in that direction is blocked.
		if (world->CheckTileValidity(World::GetTileInDirection(next_tile_, new_direction), Tile::block_type::no_block)) {
			direction_ = new_direction;
			update_image_flag_ = true;
		}
	}
}

void Avatar::Reset() {
	MovableGameEntity::Reset();

	direction_ = Vector2<char>::left;

	mouth_open_ = false;
	mouth_timer_.Reset();

	update_image_flag_ = true;
	UpdateImage();
}

unsigned char Avatar::IncrementGhostsCaughtInRow() {
	return ghosts_caught_in_row_++;
}

void Avatar::ResetGhostsCaughtInRow() {
	ghosts_caught_in_row_ = 0;
}