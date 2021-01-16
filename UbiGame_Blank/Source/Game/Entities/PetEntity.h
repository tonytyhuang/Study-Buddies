#pragma once

#include "GameEngine/EntitySystem/Entity.h"

namespace Game
{
	class PetEntity : public GameEngine::Entity {
	public:
		PetEntity();
		int GetHappiness() const { return happiness; }
		void addHappiness() {
			if (happiness >= 80) {
				happiness = 100;
			}
			else {
				happiness += 20;
			}
		}
	private:
		int happiness;
	};
}