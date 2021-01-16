#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"

#include "Game/Components/PlayerMovementComponent.h"

#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

using namespace Game;

GameBoard::GameBoard()
{
	CreatePlayer();
	CreateObstacle();
}


GameBoard::~GameBoard()
{
	
}

void GameBoard::CreatePlayer() {
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(150.0f, 150.0f));
	m_player->SetSize(sf::Vector2f(100.0f, 150.0f));

	//Render
	GameEngine::SpriteRenderComponent* render = m_player->AddComponent<GameEngine::SpriteRenderComponent>();

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Player);

	//Movement
	m_player->AddComponent<Game::PlayerMovementComponent>();  // <-- Added the movement component to the player
	m_player->AddComponent<GameEngine::CollidablePhysicsComponent>();
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
	
}