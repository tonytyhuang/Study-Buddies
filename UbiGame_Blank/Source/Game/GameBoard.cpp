#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"

#include "Game/Components/PlayerMovementComponent.h"

#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include <string>

using namespace Game;

GameBoard::GameBoard()
{
	
	SetBackground(1);
	CreatePlayer();
}


GameBoard::~GameBoard()
{
	
}

void GameBoard::SetBackground(int screen) {
	GameEngine::Entity* background = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(background);

	background->SetPos(sf::Vector2f(450.f, 150.f));
	background->SetSize(sf::Vector2f(900.f, 300.f));

	GameEngine::SpriteRenderComponent* render = background->AddComponent<GameEngine::SpriteRenderComponent>();
	if (screen == 1) {
		render->SetTexture(GameEngine::eTexture::BackgroundHome);
	}
	
	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(-1);
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
}

void GameBoard::Update()
{	
	
}