/// <author>
/// Joshua Bradley
/// </author>

#include "GameEntity.h"

#include <string>

#include "Drawer.h"
#include "Vector2.h"
#include "PacMan.h"

GameEntity::GameEntity(Vector2<float> position, const std::string& image_file_path)
		: position_(position * static_cast<float>(PacMan::kTileSize)),
			image_file_path_(image_file_path) {}

void GameEntity::Draw(const Drawer* drawer) const {
	extern const unsigned char kXOffset;
	extern const unsigned char kYOffset;

	if (!image_file_path_.empty()) {
		drawer->Draw(image_file_path_, {position_.x_ + kXOffset, position_.y_ + kYOffset});
	}
}

Vector2<float> GameEntity::position() const {
	return position_;
}

void GameEntity::set_position(Vector2<float> position) {
	position_ = position;
}

void GameEntity::set_image_file_path(const std::string& image_file_path) {
	image_file_path_ = image_file_path;
}