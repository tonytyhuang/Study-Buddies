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
		void CreatePet(float xpos, float ypos);
		void CreateText(std::string text, float xpos, float ypos, int size, std::string font);
		void CreateTasks(int id);
		void UpdateLevel();
		void SpawnBackgroundObstacles(int room);
		void CreateHappinessBar();
		void UpdateHappinessBar();
		void CreateFoodButton();
		void CreateCoin(bool main);
		void addHapiness();
		void delHappiness();
		void MouseClick();
		void CreateAgenda(bool highlight);
		void UpdateMousePosition();
		void CreateCoinCounter(std::string text, int xpos, int ypos);

		void CreateBigDog();
		void UpdateHappiness();
		void UpdatePetHappiness();
		

		void CreateCheck(bool complete, int id);


		void CreateRoom1Obstacles();

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
		bool agendaHover;
		int taskLength;
		float hapwidth;
		float haplength;
		float happiness;
		float pastHappiness;
		float happinessTime;
		int score;
		bool ispressed;
		bool enteredwith;
		std::vector<std::string> taskList;

		sf::Clock clock;

		std::vector<bool> completed;
		std::vector<bool> firstpressed;


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
		GameEngine::Entity* curText;
		GameEngine::Entity* agenda;

		std::vector<GameEngine::Entity*> tasks;
		std::vector<GameEngine::Entity*> checks;

		GameEngine::SpriteRenderComponent* playerRender;
		GameEngine::SpriteRenderComponent* petRender;

		GameEngine::SpriteRenderComponent* bigDogRender;



	};
}
