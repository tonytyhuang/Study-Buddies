#include "PlayerMovementComponent.h"

#include <SFML/Window/Keyboard.hpp>   //<-- Add the keyboard include in order to get keyboard inputs
#include "GameEngine\EntitySystem\\Components\SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine/GameEngineMain.h" //<-- Add this include to retrieve the delta time between frames

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent() : animate(nullptr)
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
    animate = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
}

void PlayerMovementComponent::Update() {
    Component::Update();

    //Grabs how much time has passed since last frame
    const float dt = GameEngine::GameEngineMain::GetTimeDelta();

    //By default the displacement is 0,0
    sf::Vector2f displacement{ 0.0f,0.0f };

    //The amount of speed that we will apply when input is received
    const float inputAmount = 150.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        direction = 1;
        displacement.x -= inputAmount * dt;
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerWalkLeft) {
                
                animate->SetIsLooping(true);
                animate->PlayAnim(GameEngine::EAnimationId::PlayerWalkLeft);
            

        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        direction = 2;
        displacement.x += inputAmount * dt;
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerWalkRight) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::PlayerWalkRight);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        direction = 3;
        displacement.y -= inputAmount * dt;
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerWalkUp) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::PlayerWalkUp);
        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        direction = 4;
        displacement.y += inputAmount * dt;
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerWalkDown) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::PlayerWalkDown);
        }
    }
    else 
    {
        if (direction == 1) {
            if (animate) {
                animate->SetIsLooping(true);
                animate->PlayAnim(GameEngine::EAnimationId::PlayerIdleLeft);
            }
        }
        else if(direction ==2){
            if (animate) {
                animate->SetIsLooping(true);
                animate->PlayAnim(GameEngine::EAnimationId::PlayerIdleRight);
            }
        }
        else if (direction == 3) {
            if (animate) {
                animate->SetIsLooping(true);
                animate->PlayAnim(GameEngine::EAnimationId::PlayerIdleUp);
            }
        }
        else if (direction == 4) {
            if (animate) {
                animate->SetIsLooping(true);
                animate->PlayAnim(GameEngine::EAnimationId::PlayerIdleDown);
            }
        }
    }

    //Update the entity position
    GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
}
