#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "Game/Entities/PlayerEntity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controlling all game related entities, as well as providing an entry point for the "game" side of application	
	//class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();
		void Update();		
		bool IsGameOver() { return false; }
		GameEngine::Entity* getPlayer();
	private:
		void CreatePlayer(float x, float y);
		void CreateObstacle();
		void CreateBackground();
		void UpdatePosition();
		void CreateChecklist();
		void CreatePet();
		void CreatePtsCounter();
		
		float boardx;
		float boardy;
		int pastscreen;
		float px;
		float py;
		int screen;
		float startx;
		float starty;
		bool init;
		bool check;

		GameEngine::Entity* pet;
		GameEngine::Entity* obstacle;
		PlayerEntity* m_player;
		GameEngine::Entity* background;
		GameEngine::Entity* checklist;
		GameEngine::Entity* ptscounter;
	};
}
