/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <string>

#include "SDL_image.h"

template <typename> struct Vector2;
struct SDL_Renderer;
struct SDL_Window;
struct SDL_Surface;

/// <summary>
/// Handles adding images and text to the drawing buffer.
/// Items in this buffer are then drawn at the end of each frame.
/// </summary>
class Drawer {
 public:
  /// <summary>
  ///  Constructor for the Drawer class.
  /// </summary>
  /// <param name="renderer">Creates SDL_Surface and SDL_Texture objects from input files.</param>
  Drawer(SDL_Renderer* renderer);
  /// <summary>
  /// Adds an image to the drawing buffer at the specified position.
  /// </summary>
  /// <param name="image_file_path">The file path for the file to draw.</param>
  /// <param name="position">The position to draw the image in pixels.</param>
  void Draw(const std::string& image_file_path, Vector2<float> position) const;
  /// <summary>
  /// Adds text to the drawing buffer at the specified position.
  /// The default colour for UI text is set to white.
  /// </summary>
  /// <param name="text">The text to display.</param>
  /// <param name="position">The position of the text</param>
  /// <param name="colour">The colour of the text.</param>
  void DrawText(const std::string& text, Vector2<float> position, SDL_Color colour = { 252, 252, 255 }) const;

 private:
  /// <summary>
  /// Creates SDL_Surface and SDL_Texture objects from input files.
  /// </summary>
  SDL_Renderer* renderer_;
};