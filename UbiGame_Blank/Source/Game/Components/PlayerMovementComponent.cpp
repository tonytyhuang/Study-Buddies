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
    const float inputAmount = 100.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {

        displacement.x -= inputAmount * dt;
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerWalkLeft) {

                animate->SetIsLooping(true);
                animate->PlayAnim(GameEngine::EAnimationId::PlayerWalkLeft);
            

        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        displacement.x += inputAmount * dt;
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerWalkRight) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::PlayerWalkRight);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        displacement.y -= inputAmount * dt;
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerWalkUp) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::PlayerWalkUp);
        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        displacement.y += inputAmount * dt;
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::PlayerWalkDown) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::PlayerWalkDown);
        }
    }
    else 
    {

        if (animate) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::PlayerIdle);
        }
    }

    


    //Update the entity position
    GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
}
