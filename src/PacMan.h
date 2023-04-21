/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <string>
#include <array>

struct SDL_Surface;
class Drawer;
class Avatar;
class World;
class Ghost;

/// <summary>
/// The game manager class.
/// </summary>
class PacMan {
 public:
	/// <summary>
	/// Creates an instance of this class. Wrapper for the constructor.
	/// </summary>
	/// <param name="drawer">Handles the drawing of game entity images and UI.</param>
	/// <returns>A pointer to an instance of this class.</returns>
	static PacMan& Instance(Drawer* drawer);
  /// <summary>
  /// Updates game entities.
  /// </summary>
	/// <param name="elapsed_millis">The amount of time in milliseconds since the previous
	/// frame update.</param>
  /// <returns>True is the frame has finished in normal conditions, false if the player
	/// has manually exited the game.</returns>
  bool Update(unsigned int elapsed_millis);
  /// <summary>
  /// Adds images representing game entities to the drawing buffer.
  /// </summary>
	/// <param name="elapsed_millis">The amount of time in milliseconds since the previous
	/// frame update.</param>
  void Draw(unsigned int elapsed_millis);
	/// <summary>
	/// Resets game entities upon the player losing a life.
	/// </summary>
	void Reset(void);
	/// <summary>
	/// The length of a square tile in pixels.
	/// </summary>
	static const int kTileSize;

 private:
	/// <summary>
	/// Constructor for the PacMan class.
	/// </summary>
	/// <param name="drawer">Handles the addition of game entity images to the drawing buffer.</param>
	PacMan(Drawer* drawer);
	/// <summary>
	/// Constructor for the PacMan class.
	/// </summary>
	PacMan(void);
  /// <summary>
  /// Handles keyboard inputs for Avatar movement and escaping the application.
	/// Includes arrow keys for 4-directional movement and escape to exit the game.
  /// </summary>
  /// <returns>True if a movement key is pressed and false if the escape key is pressed.</returns>
  bool UpdateInput(void);
  /// <summary>
  /// Cehcks whether the game's end conditions have been met, returning the result. 
  /// </summary>
  /// <returns>True if the end of the game has been reached, else false.</returns>
  bool CheckEndGameCondition(void) const;
	/// <summary>
	/// Adds the UI elements of the game to the drawing buffer.
	/// </summary>
	void DrawUI(void) const;
	/// <summary>
	/// The file path for the font used in the UI.
	/// </summary>
	static const std::string kFontFilePath;
	/// <summary>
	/// The number of milliseconds until the FPS value updates.
	/// </summary>
	int fps_counter_;
	/// <summary>
	/// Determines whether the game has ended.
	/// True if the game has ended, else false.
	/// </summary>
	bool game_over_;
	/// <summary>
	/// Draws the game entities and UI elements.
	/// </summary>
	Drawer* drawer_;
	/// <summary>
	/// The number of lives the player has remaining.
	/// </summary>
	unsigned char lives_;
	/// <summary>
	/// The player's score.
	/// </summary>
	unsigned short score_;
	/// <summary>
	/// The most recent sample of the game's FPS.
	/// </summary>
	unsigned short frames_per_second_;
	/// <summary>
	/// Holds the Avatar instance.
	/// </summary>
	Avatar* avatar_;
	/// <summary>
	/// Holds Ghost instances.
	/// </summary>
	std::array<Ghost*, 4> ghosts_;
	/// <summary>
	/// The World - responsible for map/path generation and determining whether tiles are
	/// blockages for entities.
	/// </summary>
	World* world_;
};