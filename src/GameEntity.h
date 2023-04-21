/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <string>

#include "Vector2.h"

class Drawer;

/// <summary>
/// Represents an abstract entity within the game.
/// </summary>
class GameEntity {
 public:
	/// <summary>
	/// Constructor for the GameEntity class.
	/// </summary>
	/// <param name="position">The initial tile position of the entity.</param>
	/// <param name="image_file_path">The image file path to add to the drawing buffer.</param>
	GameEntity(Vector2<float> position, const std::string& image_file_path = "");
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns>The position of the entity.</returns>
	Vector2<float> position(void) const;
	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <param name="position">The value to set the position to.</param>
	void set_position(Vector2<float> position);
	/// <summary>
	/// Handles adding the entity's image file to the drawing buffer at the entity's position.
	/// </summary>
	/// <param name="drawer">The drawer that handles adding entity images to the drawing buffer.</param>
	virtual void Draw(const Drawer* drawer) const;
	/// <summary>
	/// Sets the image file path.
	/// </summary>
	/// <param name="image_file_path">The path of the image to be drawn.</param>
	void set_image_file_path(const std::string& image_file_path);

 protected:
	/// <summary>
	/// The position of the entity.
	/// </summary>
	Vector2<float> position_;
	/// <summary>
	/// The file path of the image to be drawn.
	/// </summary>
	std::string image_file_path_;
};