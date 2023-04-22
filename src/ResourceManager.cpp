/// <author>
/// Joshua Bradley
/// </author>

#include "ResourceManager.h"

#include <unordered_map>
#include <ios>
#include <iostream>

#include "SDL_ttf.h"
#include <windows.h>
#include "SDL_image.h"

std::unordered_map<std::string, SDL_Texture*> ResourceManager::textures_ {};
TTF_Font* ResourceManager::font_ = nullptr;
std::string ResourceManager::kAssetPath;

// Prevents regular object construction.
ResourceManager::ResourceManager() {
  return;
}

ResourceManager::~ResourceManager() {
  // Releases font resources.
  if (font_ != nullptr) {
    TTF_CloseFont(font_);
  }

  // Reeases texture resources.
  for (auto& t : textures_) {
    SDL_DestroyTexture(t.second);
  }

  // Closes active SDL subsystems.
  TTF_Quit();
  IMG_Quit();
}

ResourceManager& ResourceManager::Instance() {
  static ResourceManager instance;
  
  try {
    GenerateAssetPath();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  return instance;
}

void ResourceManager::GenerateAssetPath() {
  char result[MAX_PATH]{};
  // Compatible with Windows OS.
  auto str_result = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));

  // Removes the file name from the absolute file path.
  str_result.erase(str_result.begin() + str_result.rfind("\\"), str_result.end());


  auto project_dir_pos = str_result.rfind("pacman");
  if (project_dir_pos == std::string::npos) {
    throw std::ios_base::failure("Unexpected execution environment. Executable must be ran within the project directory (\"\\pacman...\")");
  }

  str_result.replace(str_result.begin() + str_result.rfind("pacman")+6, str_result.end(),
    "\\assets\\");

  kAssetPath = str_result;
}

SDL_Texture* ResourceManager::GetTexture(std::string file_path, SDL_Renderer* renderer) {
  // Searches in cache for the requested texture.
  auto texture_iter = ResourceManager::textures_.find(file_path);

  // Inserts texture if not already present in cache.
  if (texture_iter == textures_.end()) {
    SDL_Surface* s = IMG_Load((kAssetPath + file_path).c_str());

    // Handles file being unable to load.
    if (s == NULL) {
      throw std::ios_base::failure("Cannot find/access \"" + kAssetPath + file_path + "\"");
    }

    SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);
    SDL_FreeSurface(s);

    textures_.insert({file_path, t});
  }

  return textures_[file_path];
}

void ResourceManager::set_font(const std::string& font_file_path) {
  // CLoses the currently active font.
  TTF_CloseFont(font_);

  font_ = TTF_OpenFont((kAssetPath + font_file_path).c_str(), 19);

  // Error if font cannot be located.
  if (!font_) {
    throw std::ios_base::failure("Cannot find/access \"" + kAssetPath + font_file_path + "\"");
  }
}

TTF_Font* ResourceManager::font() const {
  return font_;
}