#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "Game/Entities/PlayerEntity.h"
#include "Game/Entities/PetEntity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

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
		void CreateText(std::string text, int xpos, int ypos);
		void CreateTasks(int id);
		void UpdateLevel();
		void SpawnBackgroundObstacles(int room);
		void CreateHappinessBar();
		void UpdateHappinessBar();
		void CreateFoodButton();
		void CreateCoin();
		void addHapiness();
		void delHappiness();
		void MouseClick();
		void CreateCoinCounter(std::string text, int xpos, int ypos);
		void CreateBigDog();
		void UpdateHappiness();
		
		float boardx;
		float boardy;
		int pastscreen;
		float px;
		float py;
		float xm;
		float ym;
		int screen;
		float startx;
		float starty;
		bool init;
		bool check;
		int taskLength;
		float hapwidth;
		float haplength;
		float happiness;
		float pastHappiness;
		float happinessTime;
		int score;
		time_t lastClicked;
		bool ispressed;
		std::vector<std::string> taskList;
		sf::Clock clock;

		PetEntity* pet;
		GameEngine::Entity* obstacle;
		PlayerEntity* m_player;
		GameEngine::Entity* bigDog;
		GameEngine::Entity* background;
		GameEngine::Entity* coincounter;
		GameEngine::Entity* checklist;
		GameEngine::Entity* foodbutton;
		GameEngine::Entity* coinicon;
		GameEngine::Entity* happinessBar;
		GameEngine::Entity* happinessMeter;

		std::vector<GameEngine::Entity*> tasks;

		GameEngine::SpriteRenderComponent* playerRender;
		GameEngine::SpriteRenderComponent* petRender;
		GameEngine::SpriteRenderComponent* bigDogRender;
	};
}
