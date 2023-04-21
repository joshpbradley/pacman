/// <author>
/// Joshua Bradley
/// </author>

#include "Drawer.h"

#include <string>
#include <iostream>

#include "SDL_ttf.h"
#include "SDL_image.h"

#include "Vector2.h"
#include "ResourceManager.h"

Drawer::Drawer(SDL_Renderer* renderer)
    : renderer_(renderer) {}

void Drawer::Draw(const std::string& image_file_path, Vector2<float> position_) const {
  // Retrieves texture with the given file name.
  SDL_Texture* texture = nullptr;
  int texture_width;
  int texture_height;

  try {
    texture = ResourceManager::Instance().GetTexture(image_file_path, renderer_);
  }
  catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  // Retrieves the height and width of the supplied texture.
  SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);
  // The dimensions of the texture.
  SDL_Rect size_rect {0, 0, texture_width, texture_height};
  // The positioning and dimensions of the image.
  SDL_Rect pos_rect {static_cast<int>(position_.x_), static_cast<int>(position_.y_),
                    size_rect.w, size_rect.h};

  // Adds image to the drawing buffer.
  SDL_RenderCopy(renderer_, texture, &size_rect, &pos_rect);
}

void Drawer::DrawText(const std::string& text, Vector2<float> position_, SDL_Color colour) const {
  if (!ResourceManager::Instance().font() || text.empty()) {
    return;
  }

  // Generates high quality text SDL surface from assigned font.
  if (SDL_Surface* surface = TTF_RenderText_Shaded(ResourceManager::Instance().font(), text.c_str(), colour, {0, 0, 0})) {
    // Generates high quality SDL texture.
    if (SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface)) {
      // Dimensions of the text.
      SDL_Rect size_rect{0, 0, surface->w, surface->h};
      // Positioning and dimensions of the text.
      SDL_Rect pos_rect{static_cast<int>(position_.x_), static_cast<int>(position_.y_),
                        size_rect.w, size_rect.h};

      // Adds text to the drawing buffer.
      SDL_RenderCopy(renderer_, texture, &size_rect, &pos_rect);

      // Frees generated resources.
      SDL_DestroyTexture(texture);
      SDL_FreeSurface(surface);
    }
  }
}