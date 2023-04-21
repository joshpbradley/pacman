/// <author>
/// Joshua Bradley
/// </author>

#include "StaticGameEntity.h"
#include "GameEntity.h"

#include <string>

#include "Vector2.h"

StaticGameEntity::StaticGameEntity(Vector2<float> position, const std::string& image_file_path)
    : GameEntity(position, image_file_path) {}