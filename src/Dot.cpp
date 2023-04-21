/// <author>
/// Joshua Bradley
/// </author>

#include "Dot.h"
#include "StaticGameEntity.h"

#include "Vector2.h"

Dot::Dot(Vector2<float> position)
    : StaticGameEntity(position, "Misc\\Dot.png") {}