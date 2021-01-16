#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"

#include "Game/Components/PlayerMovementComponent.h"
#include "Game/Components/PetMovementComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include <string>
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"

using namespace Game;

GameBoard::GameBoard() : boardx(900.f), boardy(300.f), pastscreen(1), screen(1),
						 init(false), px(150), py(150),
						 m_player(nullptr), pet(nullptr), check{false}, checklist{nullptr}
{
	CreateBackground();
	CreatePtsCounter();

	// set tasks
	taskLength = 3;
	for (int i = 0; i < taskLength; ++i) {
		taskList.emplace_back("Finish probability homework");
	}
}


GameBoard::~GameBoard()
{
	
}

void GameBoard::CreateBackground() {
	GameEngine::GameEngineMain::GetInstance()->RemoveAllEntities();

	background = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(background);

	background->SetPos(sf::Vector2f(450.f, 150.f));
	background->SetSize(sf::Vector2f(900.f, 300.f));

	GameEngine::SpriteRenderComponent* render = background->AddComponent<GameEngine::SpriteRenderComponent>();
	if (screen == 1) {
		render->SetTexture(GameEngine::eTexture::BackgroundHome);
		CreateObstacle();
		if (!init) {
			CreatePlayer(px, py);
			init = true;
		}
		else {
			CreatePlayer(0.f, py);
		}
		CreatePet();
		CreateHappinessBar();
		pastscreen = 1;
	}
	else if (screen == 2) {
		render->SetTexture(GameEngine::eTexture::BackgroundHall);
		if (pastscreen == 1) {
			CreatePlayer(boardx, py);
		}
		else if (pastscreen == 3) {
			CreatePlayer(450.f, 150.f);
		}
		pastscreen = 2;
	}
	else if (screen == 3) {
		render->SetTexture(GameEngine::eTexture::BackgroundPet);


		pastscreen = 3;
	}
	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(-1);
}

void GameBoard::UpdatePosition() {
	px = m_player->GetPos().x;
	py = m_player->GetPos().y;
	printf("%f\n", px);
	printf("%f\n", py);
	if (screen == 1) {
		if (px < 0.f) {
			screen = 2;
			CreateBackground();
		}
		else if (px > 900.f) {
			if (!check) {
				CreateChecklist();
				for (int i = 0; i < taskLength; ++i) {
					CreateTasks(i);
				}
				check = true;
			}
		}
		else if (check) {
			if (checklist != nullptr) {
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(checklist);
				checklist = nullptr;
				check = false;
				for (std::vector<GameEngine::Entity*>::iterator it = tasks.begin(); it != tasks.end();) {
					GameEngine::Entity* task = (*it);
					GameEngine::GameEngineMain::GetInstance()->RemoveEntity(task);
					it = tasks.erase(it);
				}
			}
		}
	}
	else if (screen == 2) {
		
		if (px > boardx) {
			screen = 1;
			CreateBackground();
		} 
		if (px > 400.f && px < 500.f && py < 140.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			screen = 3;
			CreateBackground();
		}
	}
	else if (screen == 3) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
			screen = 2;
			CreateBackground();
		}
	}
	
}


void GameBoard::CreateChecklist() {
	checklist = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(checklist);

	checklist->SetPos(sf::Vector2f(400.0f, 150.0f));
	checklist->SetSize(sf::Vector2f(275.0f, 300.0f));

	// Render

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(checklist->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetTexture(GameEngine::eTexture::Checklist);
	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(101);

}

void GameBoard::CreateTasks(int id) {
	GameEngine::Entity* task = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(task);

	task->SetPos(sf::Vector2f(300.f, 100.f + id * 40.f));
	GameEngine::TextRenderComponent* render = task->AddComponent<GameEngine::TextRenderComponent>();
	render->SetString(taskList[id]);
	render->SetFont("joystix.ttf");
	render->SetColor(sf::Color::Black);
	render->SetFillColor(sf::Color::Transparent);
	render->SetCharacterSizePixels(20);
	render->SetZLevel(102);

	tasks.push_back(task);
}

void GameBoard::CreatePlayer(float x, float y) {
	m_player = new PlayerEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(x, y));
	m_player->SetSize(sf::Vector2f(50.0f, 75.0f));

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

void GameBoard::CreatePet() {
	pet = new PetEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(pet);

	pet->SetPos(sf::Vector2f(700.0f, 150.0f));
	pet->SetSize(sf::Vector2f(50.0f, 50.0f));

	petRender = static_cast<GameEngine::SpriteRenderComponent*>(pet->AddComponent<GameEngine::SpriteRenderComponent>());

	petRender->SetFillColor(sf::Color::Transparent);
	petRender->SetTexture(GameEngine::eTexture::Dog);
	petRender->SetZLevel(99);

	pet->AddComponent<GameEngine::AnimationComponent>();
	Game::PetMovementComponent* temp =  pet->AddComponent<Game::PetMovementComponent>();

	temp->SetPlayerEntity(m_player);
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

void GameBoard::CreatePtsCounter() {
	ptscounter = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(ptscounter);

	ptscounter->SetPos(sf::Vector2f(0.f, 0.f));
	GameEngine::TextRenderComponent* render = ptscounter->AddComponent<GameEngine::TextRenderComponent>();
	render->SetString("Fun Points! : " + std::to_string(m_player->GetScore()));
	render->SetFont("joystix.ttf");
	render->SetColor(sf::Color::Black);
	render->SetFillColor(sf::Color::Transparent);
	render->SetCharacterSizePixels(20);
}

void GameBoard::CreateHappinessBar() {
	happinessBar = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(happinessBar);

	happinessBar->SetPos(sf::Vector2f(750.f, 10.f));
	happinessBar->SetSize(sf::Vector2f(208.f, 18.f));
	GameEngine::SpriteRenderComponent* render = happinessBar->AddComponent<GameEngine::SpriteRenderComponent>();

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::HappinessBar);
	render->SetZLevel(100);




}

void GameBoard::UpdateLevel() {
	if (m_player->GetPos().y < (pet->GetPos().y - 12.f)) {
		playerRender->SetZLevel(99);
		petRender->SetZLevel(100);
	}
	else {
		playerRender->SetZLevel(100);
		petRender->SetZLevel(99);
	}
}

void GameBoard::Update()
{	
	UpdateLevel();
	UpdatePosition();
}

GameEngine::Entity* GameBoard::getPlayer() {
	return m_player;
}