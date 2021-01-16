#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "Game/Entities/PlayerEntity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

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
		void CreatePlayer();
		void CreateObstacle();
		void SetBackground();
		void UpdatePosition();
		void CreateChecklist();
		void CreatePet();
		void CreatePtsCounter();
		void CreateTasks(int id);
		
		float boardx;
		float boardy;
		int screen;
		bool check;
		int taskLength;
		std::vector<std::string> taskList;

		GameEngine::Entity* pet;
		GameEngine::Entity* obstacle;
		PlayerEntity* m_player;
		GameEngine::Entity* background;
		GameEngine::Entity* checklist;
		GameEngine::Entity* ptscounter;
		std::vector<GameEngine::Entity*> tasks;
	};
}

