/// <author>
/// Joshua Bradley
/// </author>

#include "PowerPellet.h"
#include "StaticGameEntity.h"

#include <list>

#include "Vector2.h"

Timer PowerPellet::blink_timer_ = Timer(100, true);
bool PowerPellet::draw_ = true;

PowerPellet::PowerPellet(Vector2<float> position)
    : StaticGameEntity(position, "Misc\\Power-Pellet.png") {}


bool PowerPellet::Draw(const Drawer* drawer, unsigned int elapsed_millis, std::list<PowerPellet*>& power_pellets) {
	if (blink_timer_.Update(elapsed_millis)) {
		draw_ = !draw_;
	}

	if (draw_) {
		// Draw Power Pellets.
		for (auto power_pellet : power_pellets) {
			power_pellet->GameEntity::Draw(drawer);
		}
	}

	return draw_;
}