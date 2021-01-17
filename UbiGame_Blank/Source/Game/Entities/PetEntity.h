#pragma once

#include "GameEngine/EntitySystem/Entity.h"

namespace Game
{
	class PetEntity : public GameEngine::Entity {
	public:
		PetEntity();
		float GetHappiness() const { return happiness; }
		void addHappiness() {
			if (happiness >= 0.8) {
				happiness = 1.f;
			}
			else {
				happiness += 0.2;
			}
		}
		void removeHappiness() {
			if (happiness > 0.19) {
				happiness -= 0.2;
			}
		}
	private:
		float happiness;
	};
}