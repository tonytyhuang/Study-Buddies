#pragma once

#include "GameEngine/EntitySystem/Entity.h"

namespace Game
{
	class PlayerEntity : public GameEngine::Entity {
	public:
		PlayerEntity();
		int GetScore() const { return score; }
	private:
		int score;
	};
}