/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <unordered_map>
#include <string>

#include "SDL_ttf.h"

struct SDL_Renderer;
struct SDL_Texture;

/// <summary>
///  Handles the SDL resources caching and retrieval.
/// </summary>
class ResourceManager {
 public:
  static std::string kAssetPath;
  /// <summary>
  /// Retrieves a singleton instance of the ResourceManager class.
  /// </summary>
  /// <returns>A singleton instance of the ResourceManager class.</returns>
  static ResourceManager& Instance(void);
  /// <summary>
  /// Gets the texture from the cache with the specified file path.
  /// If the texture is not already present, it is placed into the cache.
  /// Returns NULL on error.
  /// </summary>
  /// <param name="file_path">The path of the file to retrieve.</param>
  /// <param name="renderer">Renders the SDL_Sirface and SDL_Texture components.</param>
  /// <returns></returns>
  SDL_Texture* GetTexture(std::string file_path, SDL_Renderer* renderer);
  /// <summary>
  /// Sets the path of the font file to be set as the game's active font.
  /// </summary>
  /// <param name="font_file_path">The path of the font to load into the game.</param>
  void set_font(const std::string& font_file_path);
  /// <summary>
  /// Gets the active font.
  /// </summary>
  /// <returns>The active font.</returns>
  TTF_Font* font(void) const;

 private:
  /// <summary>
  /// Constructor for the ResourceManager class.
  /// </summary>
  ResourceManager(void);
  /// <summary>
  /// Destructor for the ResourceManager class.
  /// Safely releases SDL resources.
  /// </summary>
  ~ResourceManager(void);
  /// <summary>
  /// Copy constructor for the ResourceManager class.
  /// </summary>
  /// <param name="reference">The ResourceManager reference to copy.</param>
  ResourceManager(ResourceManager const& reference);
  /// <summary>
  /// Generates an absolute file path to the "assets" folder. Used for retrieving game assets.
  /// </summary>
  static void GenerateAssetPath(void);
  /// <summary>
  /// Stores the file path (key) with the Texture pointer (value).
  /// </summary>
  static std::unordered_map<std::string, SDL_Texture*> textures_;
  /// <summary>
  /// Stores the font that is to be applied to in-game text.
  /// </summary>
  static TTF_Font* font_;
};