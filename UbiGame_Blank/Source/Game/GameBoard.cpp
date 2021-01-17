#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"

#include "Game/Components/PlayerMovementComponent.h"
#include "Game/Components/PetMovementComponent.h"
#include "Game/Components/BigDogComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace Game;

GameBoard::GameBoard() : boardx(1800.f), boardy(900.f), pastscreen(1), screen(1), agendaHover(false),
init(false), px(500), py(500), hapwidth(416.0), haplength(32.0), pastHappiness(1.f),
m_player(nullptr), pet(nullptr), check{ false }, checklist{ nullptr }, happinessTime(15.0),
ispressed(false), score(100), happiness(0.6), taskLength(3)

{
	sf::Time time1 = clock.restart();
	CreateBackground();

	// set tasks
	// done manually for now
	taskList.emplace_back("Attend morning class");
	taskList.emplace_back("Finish probability homework");
	taskList.emplace_back("Math Club!");
	for (int i = 0; i < taskLength; ++i) {
		completed.emplace_back(false);
		firstpressed.emplace_back(true);
	}
}


GameBoard::~GameBoard()
{

}

void GameBoard::CreateBackground() {
	GameEngine::GameEngineMain::GetInstance()->RemoveAllEntities();

	background = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(background);

	background->SetPos(sf::Vector2f(900, 450.f));
	background->SetSize(sf::Vector2f(boardx, boardy));

	GameEngine::SpriteRenderComponent* render = background->AddComponent<GameEngine::SpriteRenderComponent>();
	if (screen == 1) {
		render->SetTexture(GameEngine::eTexture::BackgroundHome);
		CreateRoom1Obstacles();
		CreateAgenda(false);
		for (int i = 0; i < 8; ++i) {
			SpawnBackgroundObstacles(100 + i);
		}
		//CreateObstacle();
		if (!init) {
			CreatePlayer(px, py);
			CreateText("Welcome to StudyBuddies! Use the arrow keys to move around.", 250.f, 825.f, 25, "pokemon.ttf");
			init = true;
		}
		else if (pastscreen == 2) {
			CreatePlayer(0.f, py);
		}
		else if (pastscreen == 4) {
			CreatePlayer(boardx, py);
		}
		CreatePet(1390.0f, 410.0f);
		CreateHappinessBar();
		CreateCoinCounter("Coins: " + std::to_string(score), 150.f, 50.f);
		CreateCoin(true);
		pastscreen = 1;
	}
	else if (screen == 2) {
		render->SetTexture(GameEngine::eTexture::BackgroundHall);
		for (int i = 0; i < 3; ++i) {
			SpawnBackgroundObstacles(200 + i);
		}
		if (pastscreen == 1) {
			CreatePlayer(boardx, py);
		}
		else if (pastscreen == 3) {
			CreatePlayer(880.f, 500.f);
		}
		CreateHappinessBar();
		CreateCoinCounter("Coins: " + std::to_string(score), 150.f, 50.f);
		CreateCoin(true);
		pastscreen = 2;
	}
	else if (screen == 3) {
		render->SetTexture(GameEngine::eTexture::BackgroundPet);

		CreateHappinessBar();
		CreateCoinCounter("Coins: " + std::to_string(score), 175.f, 75.f);
		CreateText("Feed Pet (10C)", 175.f, 275.f, 35, "joystix.ttf");
		CreateFoodButton();
		CreateCoin(false);
		CreateBigDog();
		pastscreen = 3;
	}
	else if (screen == 4) {
		render->SetTexture(GameEngine::eTexture::BackgroundWalk);
		for (int i = 0; i < 5; ++i) {
			SpawnBackgroundObstacles(400 + i);
		}
		CreatePlayer(0.f, py);
		pastscreen = 4;
		if (happiness > 0.3f) {
			CreatePet(0.f, py - 75.f);
			CreateHappinessBar();
		}
	}
	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(-1);
}

void GameBoard::CreateRoom1Obstacles() {
	GameEngine::Entity* table1 = new GameEngine::Entity();
	GameEngine::Entity* table2 = new GameEngine::Entity();
	GameEngine::Entity* table3 = new GameEngine::Entity();
	GameEngine::Entity* desk = new GameEngine::Entity();
	GameEngine::Entity* dogPillow = new GameEngine::Entity();

	GameEngine::GameEngineMain::GetInstance()->AddEntity(table1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(table2);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(table3);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(desk);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(dogPillow);

	table1->SetPos(sf::Vector2f(620.0f, 375.0f));
	table2->SetPos(sf::Vector2f(770.0f, 375.0f));
	table3->SetPos(sf::Vector2f(920.0f, 375.0f));
	desk->SetPos(sf::Vector2f(800.0f, 450.0f));
	dogPillow->SetPos(sf::Vector2f(1400.0f, 430.0f));
	
	table1->SetSize(sf::Vector2f(1600.0f, 800.0f));
	table2->SetSize(sf::Vector2f(1600.0f, 800.0f));
	table3->SetSize(sf::Vector2f(1600.0f, 800.0f));
	desk->SetSize(sf::Vector2f(1600.0f, 800.0f));
	dogPillow->SetSize(sf::Vector2f(300.0f, 300.0f));

	// Render

	GameEngine::SpriteRenderComponent* render1 = static_cast<GameEngine::SpriteRenderComponent*>(table1->AddComponent<GameEngine::SpriteRenderComponent>());
	GameEngine::SpriteRenderComponent* render2 = static_cast<GameEngine::SpriteRenderComponent*>(table2->AddComponent<GameEngine::SpriteRenderComponent>());
	GameEngine::SpriteRenderComponent* render3 = static_cast<GameEngine::SpriteRenderComponent*>(table3->AddComponent<GameEngine::SpriteRenderComponent>());
	GameEngine::SpriteRenderComponent* render4 = static_cast<GameEngine::SpriteRenderComponent*>(desk->AddComponent<GameEngine::SpriteRenderComponent>());
	GameEngine::SpriteRenderComponent* render5 = static_cast<GameEngine::SpriteRenderComponent*>(dogPillow->AddComponent<GameEngine::SpriteRenderComponent>());

	render1->SetTexture(GameEngine::eTexture::Table1);
	render2->SetTexture(GameEngine::eTexture::Table2);
	render3->SetTexture(GameEngine::eTexture::Table3);
	render4->SetTexture(GameEngine::eTexture::Desk);
	render5->SetTexture(GameEngine::eTexture::DogPillow);

	render1->SetFillColor(sf::Color::Transparent);
	render2->SetFillColor(sf::Color::Transparent);
	render3->SetFillColor(sf::Color::Transparent);
	render4->SetFillColor(sf::Color::Transparent);
	render5->SetFillColor(sf::Color::Transparent);

	render1->SetZLevel(100);
	render2->SetZLevel(100);
	render3->SetZLevel(100);
	render4->SetZLevel(100);
	render5->SetZLevel(50);
}

void GameBoard::CreateAgenda(bool highlight) {
	agenda = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(agenda);

	agenda->SetPos(sf::Vector2f(900.0f, 430.0f));
	agenda->SetSize(sf::Vector2f(1600.0f, 800.0f));

	GameEngine::SpriteRenderComponent* render = agenda->AddComponent<GameEngine::SpriteRenderComponent>();

	render->SetFillColor(sf::Color::Transparent);

	render->SetZLevel(1);
	if (highlight) {
		render->SetTexture(GameEngine::eTexture::AgendaHover);
	}
	else {
		render->SetTexture(GameEngine::eTexture::Agenda);
	}
}


void GameBoard::UpdateMousePosition() {
	//GameEngine::Entity* window = new GameEngine::Entity();
	sf::RenderWindow* window = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow();
	sf::Event event;

	if (screen == 1) {
		// while there are pending events...
		while (window->pollEvent(event))
		{

			if ((sf::Mouse::getPosition().x > 700 && sf::Mouse::getPosition().x < 1200) && (sf::Mouse::getPosition().y > 160 && sf::Mouse::getPosition().y < 400)) {
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(agenda);
				agenda = nullptr;
				CreateAgenda(true);
				agendaHover = true;
			}
			else if (agendaHover) {
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(agenda);
				agenda = nullptr;
				CreateAgenda(false);
				agendaHover = false;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (agendaHover) {
				if (!check) {
					CreateChecklist();
					for (int i = 0; i < taskLength; ++i) {
						CreateTasks(i);
						CreateCheck(completed[i], i);
					}
					check = true;
				}
			}
		}

		if (check && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(checklist);
			checklist = nullptr;
			check = false;
			for (std::vector<GameEngine::Entity*>::iterator it = tasks.begin(); it != tasks.end();) {
				GameEngine::Entity* task = (*it);
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(task);
				it = tasks.erase(it);
			}
			for (std::vector<GameEngine::Entity*>::iterator it = checks.begin(); it != checks.end();) {
				GameEngine::Entity* task = (*it);
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(task);
				it = checks.erase(it);
			}
		}
		else if (check) {
			bool checkpressed = false;
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				float xmcur = sf::Mouse::getPosition().x;
				float ymcur = sf::Mouse::getPosition().y;
				
				if (xmcur > 600 && xmcur < 1300) {
					for (int i = 0; i < taskLength; ++i) {
						if (ymcur > (410 + i * 90) && ymcur < (460 + i * 90)) {
							if (firstpressed[i]) {
								score += 10;
							}
							firstpressed[i] = false;
							completed[i] = true;
							CreateCheck(completed[i], i);
							checkpressed = true;
						}
					}
				}
			}
			if (checkpressed) {
				score += 10;
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(coincounter);
				coincounter = nullptr;
				CreateCoinCounter("Coins: " + std::to_string(score), 150.f, 50.f);
			}
		}
	}
}


void GameBoard::UpdatePosition() {
	px = m_player->GetPos().x;
	py = m_player->GetPos().y;

	if (screen == 1) {
		if (px < 0.f) {
			screen = 2;
			CreateBackground();
		}
		else if (px > boardx) {
			screen = 4;
			CreateBackground();
		}
	}
	else if (screen == 2) {
		if (px > boardx) {
			screen = 1;
			CreateBackground();
		}
		if (px > 800.f && px < 1000.f && py < 600.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			screen = 3;
			CreateBackground();
		}
	}
	else if (screen == 3) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
			screen = 2;
			CreateBackground();
		}

		while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			xm = sf::Mouse::getPosition().x;
			ym = sf::Mouse::getPosition().y;
			ispressed = true;
		}
		if (ispressed && xm < 650 && xm > 100 && ym > 300 && ym < 500) {
			if (score > 0) {
				score = score - 10;
				addHapiness();
				ispressed = false;
				xm = 0;
				ym = 0;
				if (coincounter) {
					GameEngine::GameEngineMain::GetInstance()->RemoveEntity(coincounter);
					coincounter = nullptr;
				}

				CreateCoinCounter("Coins: " + std::to_string(score), 175.f, 75.f);
			}
			else {
				CreateText("Not enough coins! Complete more tasks :)", 200.f, 850.f, 25, "joystix.ttf");
			}
		}
	}
	else if (screen == 4) {
		if (px < 0.f) {
			screen = 1;
			CreateBackground();
		}
	}
}


void GameBoard::CreateChecklist() {
	checklist = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(checklist);

	checklist->SetPos(sf::Vector2f(900.0f, 450.0f));
	checklist->SetSize(sf::Vector2f(1000.0f, 500.0f));

	// Render

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(checklist->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetTexture(GameEngine::eTexture::Checklist);
	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(101);

}

void GameBoard::CreateTasks(int id) {
	GameEngine::Entity* task = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(task);

	task->SetPos(sf::Vector2f(550.f, 300.f + id * 90.f));
	GameEngine::TextRenderComponent* render = task->AddComponent<GameEngine::TextRenderComponent>();
	render->SetString(taskList[id]);
	render->SetFont("pokemon.ttf");
	render->SetColor(sf::Color::Black);
	render->SetFillColor(sf::Color::Transparent);
	render->SetCharacterSizePixels(25);
	render->SetZLevel(102);

	tasks.push_back(task);
}


void GameBoard::CreatePlayer(float x, float y) {
	m_player = new PlayerEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(x, y));
	m_player->SetSize(sf::Vector2f(100.0f, 150.0f));

	//Render
	playerRender = static_cast<GameEngine::SpriteRenderComponent*>(m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	playerRender->SetFillColor(sf::Color::Transparent);
	playerRender->SetTexture(GameEngine::eTexture::Player);
	playerRender->SetZLevel(100); // Player in front of everything

	//Movement
	m_player->AddComponent<Game::PlayerMovementComponent>();  // <-- Added the movement component to the player
	m_player->AddComponent<GameEngine::AnimationComponent>();
	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}

void GameBoard::SpawnBackgroundObstacles(int id) {
	GameEngine::Entity* obst = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obst);
	if (id == 200) {
		obst->SetPos(sf::Vector2f(0, 0.f));
		obst->SetSize(sf::Vector2f(3600.0f, 900.0f));
	}
	else if (id == 201) {
		obst->SetPos(sf::Vector2f(0, 1000.f));
		obst->SetSize(sf::Vector2f(3600.0f, 100.0f));
	}
	else if (id == 202) {
		obst->SetPos(sf::Vector2f(0, 0.f));
		obst->SetSize(sf::Vector2f(5.0f, 4000.0f));
	}
	else if (id == 100) {
		obst->SetPos(sf::Vector2f(0, 0.f));
		obst->SetSize(sf::Vector2f(450.0f, 1000.0f));
	}
	else if (id == 101) {
		obst->SetPos(sf::Vector2f(450.f, 0.f));
		obst->SetSize(sf::Vector2f(2300.0f, 550.0f));
	}
	else if (id == 102) {
		obst->SetPos(sf::Vector2f(1780.f, 0.f));
		obst->SetSize(sf::Vector2f(450.0f, 1000.0f));
	}
	else if (id == 103) {
		obst->SetPos(sf::Vector2f(0.f, 960.f));
		obst->SetSize(sf::Vector2f(4000.0f, 10.0f));
	}
	else if (id == 104) {
		obst->SetPos(sf::Vector2f(375.f, 680.f));
		obst->SetSize(sf::Vector2f(240.0f, 40.0f));
	}
	else if (id == 105) {
		obst->SetPos(sf::Vector2f(855.f, 680.f));
		obst->SetSize(sf::Vector2f(240.0f, 40.0f));
	}
	else if (id == 106) {
		obst->SetPos(sf::Vector2f(1355.f, 680.f));
		obst->SetSize(sf::Vector2f(240.0f, 40.0f));
	}
	else if (id == 107) {
		obst->SetPos(sf::Vector2f(500.f, 440.f));
		obst->SetSize(sf::Vector2f(300.0f, 30.0f));
	}
	else if (id == 400) {
		obst->SetPos(sf::Vector2f(0.f, 0.f));
		obst->SetSize(sf::Vector2f(4000.0f, 300.0f));
	}
	else if (id == 401) {
		obst->SetPos(sf::Vector2f(0.f, 0.f));
		obst->SetSize(sf::Vector2f(700.0f, 750.0f));
	}
	else if (id == 402) {
		obst->SetPos(sf::Vector2f(400.f, 200.f));
		obst->SetSize(sf::Vector2f(200.0f, 130.0f));
	}
	else if (id == 403) {
		obst->SetPos(sf::Vector2f(1800.f, 0.f));
		obst->SetSize(sf::Vector2f(300.0f, 750.0f));
	}
	else if (id == 404) {
		obst->SetPos(sf::Vector2f(1500.f, 0.f));
		obst->SetSize(sf::Vector2f(400.0f, 500.0f));
	}
	

	// Render
	GameEngine::SpriteRenderComponent* render = obst->AddComponent<GameEngine::SpriteRenderComponent>();

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::HallObstacle);

	//comment out to show the obstacle
	render->SetZLevel(-8);

	obst->AddComponent<GameEngine::CollidableComponent>();
	//roomObstacles.push_back(obst);
}

void GameBoard::CreatePet(float xpos, float ypos) {
	pet = new PetEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(pet);

	pet->SetPos(sf::Vector2f(xpos, ypos));
	pet->SetSize(sf::Vector2f(100.0f, 100.0f));

	petRender = static_cast<GameEngine::SpriteRenderComponent*>(pet->AddComponent<GameEngine::SpriteRenderComponent>());

	petRender->SetFillColor(sf::Color::Transparent);
	petRender->SetTexture(GameEngine::eTexture::Dog);
	petRender->SetZLevel(99);

	pet->AddComponent<GameEngine::AnimationComponent>();
	Game::PetMovementComponent* temp = pet->AddComponent<Game::PetMovementComponent>();

	temp->SetPlayerEntity(m_player);
	temp->GetHappiness(happiness);
}

void GameBoard::CreateBigDog() {
	bigDog = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bigDog);

	bigDog->SetPos(sf::Vector2f(1150.f, 400.f));
	bigDog->SetSize(sf::Vector2f(450.f, 750.f));

	bigDogRender = static_cast<GameEngine::SpriteRenderComponent*>(bigDog->AddComponent<GameEngine::SpriteRenderComponent>());

	bigDogRender->SetFillColor(sf::Color::Transparent);
	bigDogRender->SetTexture(GameEngine::eTexture::BigDog);
	bigDogRender->SetZLevel(200);

	bigDog->AddComponent<GameEngine::AnimationComponent>();
	Game::BigDogComponent* temp = bigDog->AddComponent<Game::BigDogComponent>();

	temp->SetHappiness(happiness);
}



void GameBoard::CreateObstacle() {
	obstacle = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);

	obstacle->SetPos(sf::Vector2f(350.f, 150.f));
	obstacle->SetSize(sf::Vector2f(100.0f, 120.0f));

	// Render
	GameEngine::SpriteRenderComponent* render = obstacle->AddComponent<GameEngine::SpriteRenderComponent>();

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Obstacle);

	obstacle->AddComponent<GameEngine::CollidableComponent>();

}


void GameBoard::CreateCheck(bool complete, int id) {
	GameEngine::Entity* mark = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(mark);
	mark->SetPos(sf::Vector2f(500.f, 315.f + id * 90.f));
	mark->SetSize(sf::Vector2f(50.f, 50.f));
	GameEngine::SpriteRenderComponent* render = mark->AddComponent<GameEngine::SpriteRenderComponent>();
	
	if (complete) {
		render->SetTexture(GameEngine::eTexture::Check);
		render->SetFillColor(sf::Color::Color(16, 112, 6));
	}
	else {
		render->SetTexture(GameEngine::eTexture::Cross);
		render->SetFillColor(sf::Color::Transparent);
	}
	render->SetZLevel(102);
	checks.push_back(mark);
}


void GameBoard::CreateFoodButton() {
	foodbutton = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(foodbutton);
	foodbutton->SetPos(sf::Vector2f(100.0f, 300.0f));
	foodbutton->SetSize(sf::Vector2f(200.f, 200.f));
	GameEngine::SpriteRenderComponent* render = foodbutton->AddComponent<GameEngine::SpriteRenderComponent>();
	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::DogFood);
}


void GameBoard::CreateCoin(bool main) {
	coinicon = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(coinicon);
	if (!main) {
		coinicon->SetPos(sf::Vector2f(100.f, 100.f));
		coinicon->SetSize(sf::Vector2f(175.f, 175.f));
	}
	else {
		coinicon->SetPos(sf::Vector2f(90.f, 75.f));
		coinicon->SetSize(sf::Vector2f(100.f, 100.f));
	}
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(coinicon->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Coin);
}

void GameBoard::CreateCoinCounter(std::string text, int xpos, int ypos) {
	coincounter = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(coincounter);

	coincounter->SetPos(sf::Vector2f(xpos, ypos));
	GameEngine::TextRenderComponent* render = coincounter->AddComponent<GameEngine::TextRenderComponent>();
	render->SetString(text);
	render->SetFont("joystix.ttf");
	render->SetColor(sf::Color::Black);
	render->SetFillColor(sf::Color::Transparent);
	render->SetCharacterSizePixels(35);
}

void GameBoard::CreateText(std::string text, float xpos, float ypos, int size, std::string font) {
	curText = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(curText);

	curText->SetPos(sf::Vector2f(xpos, ypos));
	GameEngine::TextRenderComponent* render = curText->AddComponent<GameEngine::TextRenderComponent>();
	render->SetString(text);
	render->SetFont(font);
	render->SetColor(sf::Color::Black);
	render->SetFillColor(sf::Color::Transparent);
	render->SetCharacterSizePixels(size);
}


void GameBoard::CreateHappinessBar() {
	happinessBar = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(happinessBar);

	happinessMeter = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(happinessMeter);

	happinessBar->SetPos(sf::Vector2f(1550.f, 40.f));
	happinessBar->SetSize(sf::Vector2f(hapwidth, haplength));
	GameEngine::SpriteRenderComponent* render = happinessBar->AddComponent<GameEngine::SpriteRenderComponent>();

	if (happiness > 0.99) {
		happinessMeter->SetPos(sf::Vector2f(1550.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth, haplength));
	}
	else if (happiness > 0.79) {
		happinessMeter->SetPos(sf::Vector2f(1510.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth * 0.8, haplength));
	}
	else if (happiness > 0.59) {
		happinessMeter->SetPos(sf::Vector2f(1470.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth * 0.6, haplength));
	}
	else if (happiness > 0.39) {
		happinessMeter->SetPos(sf::Vector2f(1430.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth * 0.4, haplength));
	}
	else if (happiness > 0.19) {
		happinessMeter->SetPos(sf::Vector2f(1390.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth * 0.2, haplength));
	}
	else if (happiness == 0) {
		happinessMeter->SetPos(sf::Vector2f(1550.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(0, haplength));
	}

	GameEngine::RenderComponent* meter = static_cast<GameEngine::RenderComponent*>(happinessMeter->AddComponent<GameEngine::RenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::HappinessBar);
	render->SetZLevel(300);

	meter->SetFillColor(sf::Color::Green);
	render->SetZLevel(200);
}

void GameBoard::addHapiness() {
	if (happiness >= 0.8) {
		happiness = 1.f;
	}
	else {
		happiness += 0.2;
	}
}

void GameBoard::UpdateHappinessBar() {

	if (happiness > 0.99) {
		happinessMeter->SetPos(sf::Vector2f(1550.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth, haplength));
	}
	else if (happiness > 0.79) {
		happinessMeter->SetPos(sf::Vector2f(1510.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth * 0.8, haplength));
	}
	else if (happiness > 0.59) {
		happinessMeter->SetPos(sf::Vector2f(1470.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth * 0.6, haplength));
	}
	else if (happiness > 0.39) {
		happinessMeter->SetPos(sf::Vector2f(1430.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth * 0.4, haplength));
	}
	else if (happiness > 0.19) {
		happinessMeter->SetPos(sf::Vector2f(1390.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(hapwidth * 0.2, haplength));
	}
	else if (happiness == 0) {
		happinessMeter->SetPos(sf::Vector2f(1550.f, 40.f));
		happinessMeter->SetSize(sf::Vector2f(0, haplength));
	}

}

void GameBoard::UpdateLevel() {
	if (screen == 1 || screen == 4) {
		if (m_player->GetPos().y < (pet->GetPos().y - 12.f)) {
			playerRender->SetZLevel(99);
			petRender->SetZLevel(100);
		}
		else {
			playerRender->SetZLevel(100);
			petRender->SetZLevel(99);
		}
	}

}
void GameBoard::delHappiness() {
	if (happiness > 0.39) {
		happiness -= 0.2;
	}
}

void GameBoard::UpdateHappiness() {
	sf::Time time1 = clock.getElapsedTime();
	if (time1.asSeconds() > happinessTime) {
		delHappiness();
		clock.restart();
	}
}

void GameBoard::UpdatePetHappiness() {
	if (screen == 1 || screen == 4) {
		Game::PetMovementComponent* temp = pet->GetComponent<Game::PetMovementComponent>();
		temp->GetHappiness(happiness);
	}
	else if (screen == 3) {
		Game::BigDogComponent* temp2 = bigDog->GetComponent<Game::BigDogComponent>();
		temp2->SetHappiness(happiness);
	}
}
//void GameBoard::StartText() {




/*
	if (!enter2) {
		CreateText("Welcome to VPets! Use the arrow keys to move around.", 250.f, 825.f, 25, "pokemon.ttf");
		//CreateText("Your pet tired and sleeping. Move left of the screen to feed it.", 200.f, 850.f, 25, "pokemon.ttf");
	}
	
	else if (passed < 16 && !enter2) {
		CreateText("Your pet tired and sleeping. Move left of the screen to feed it.", 200.f, 825.f, 25, "pokemon.ttf");
	}
	else if (enter2 && init2) {
		if (passed > 24) {
			init2 = false;
		}
		CreateText("Move to the door and press Enter to feed your pet!", 100.f, 825.f, 25, "pokemon.ttf");
	}
	else if (enter3 && init3) {
		if (passed > 32) {
			init3 = false;
		}
		init2 = false;
		CreateText("Click Feed to restore your pet's energy.", 100.f, 825.f, 25, "pokemon.ttf");
	}
	else if (enter4 && init4) {
		if (passed > 40) {
			init4 = false;
		}
		init3 = false;
		CreateText("Check your pet :)", 300.f, 825.f, 25, "pokemon.ttf");
	}*/

void GameBoard::MouseClick() {

}

void GameBoard::Update()
{
	
	UpdatePetHappiness();
	
	UpdateHappiness();
	UpdateHappinessBar();
	UpdateLevel();
	UpdatePosition();
	UpdateMousePosition();
}

GameEngine::Entity* GameBoard::getPlayer() {
	return m_player;
}