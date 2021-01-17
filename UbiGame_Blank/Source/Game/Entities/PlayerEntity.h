#pragma once

#include "GameEngine/EntitySystem/Entity.h"

namespace Game
{
	class PlayerEntity : public GameEngine::Entity {
	public:
		PlayerEntity();
		void SetScore(int nscore) { score = nscore; }
		int GetScore() const { return score; }
	private:
		int score;
	};
}