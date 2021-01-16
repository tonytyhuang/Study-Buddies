#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"

#include "Game/Components/PlayerMovementComponent.h"
#include "Game/Components/PetMovementComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include <string>
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

using namespace Game;

GameBoard::GameBoard() : m_player(nullptr), pet(nullptr)
{
	boardx = 900.f;
	boardy = 300.f;
	screen = 1;
	SetBackground();
	CreatePlayer();
	CreatePet();
	CreateObstacle();
}


GameBoard::~GameBoard()
{
	
}

void GameBoard::SetBackground() {
	background = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(background);

	background->SetPos(sf::Vector2f(450.f, 150.f));
	background->SetSize(sf::Vector2f(900.f, 300.f));

	GameEngine::SpriteRenderComponent* render = background->AddComponent<GameEngine::SpriteRenderComponent>();
	if (screen == 1) {
		render->SetTexture(GameEngine::eTexture::BackgroundHome);
	}
	else if (screen == 2) {
		render->SetTexture(GameEngine::eTexture::BackgroundHall);
	}

	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(-1);
}

void GameBoard::UpdatePosition() {
	float xpos = m_player->GetPos().x;
	float ypos = m_player->GetPos().y;

	if (screen == 1) {
		if (xpos < 0.f) {
			screen = 2;
			SetBackground();
			m_player->SetPos(sf::Vector2f(boardx, 150.f));
		}
	}
	else if (screen == 2) {
		if (xpos > boardx) {
			screen = 1;
			SetBackground();
			m_player->SetPos(sf::Vector2f(0.f, 150.f));
		}
	}
}

void GameBoard::CreatePlayer() {
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(150.0f, 150.0f));
	m_player->SetSize(sf::Vector2f(50.0f, 75.0f));

	//Render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Player);
	render->SetZLevel(100); // Player in front of everything

	//Movement
	m_player->AddComponent<Game::PlayerMovementComponent>();  // <-- Added the movement component to the player
	m_player->AddComponent<GameEngine::AnimationComponent>();
	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
}

void GameBoard::CreatePet() {
	pet = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(pet);

	pet->SetPos(sf::Vector2f(200.0f, 150.0f));
	pet->SetSize(sf::Vector2f(50.0f, 50.0f));

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(pet->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Dog);

	pet->AddComponent<GameEngine::AnimationComponent>();
	pet->AddComponent<Game::PetMovementComponent>();



}

void GameBoard::CreateObstacle() {
	obstacle = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);

	obstacle->SetPos(sf:: Vector2f(350.f, 150.f));
	obstacle->SetSize(sf::Vector2f(100.0f, 120.0f));

	// Render
	GameEngine::SpriteRenderComponent* render = obstacle->AddComponent<GameEngine::SpriteRenderComponent>();

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Obstacle);

	obstacle->AddComponent<GameEngine::CollidableComponent>();

}

void GameBoard::Update()
{	
	UpdatePosition();
}