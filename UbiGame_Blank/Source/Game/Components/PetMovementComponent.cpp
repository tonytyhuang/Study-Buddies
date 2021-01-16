#include "PlayerMovementComponent.h"

#include <SFML/Window/Keyboard.hpp>   //<-- Add the keyboard include in order to get keyboard inputs
#include "GameEngine\EntitySystem\\Components\SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine/GameEngineMain.h" //<-- Add this include to retrieve the delta time between frames

using namespace Game;

PetMovementComponent::PetMovementComponent() : animate(nullptr)
{

}

PetMovementComponent::~PetMovementComponent()
{

}

void PetMovementComponent::OnAddToWorld()
{
    animate = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
}

void PetMovementComponent::Update() {
    Component::Update();

    //Grabs how much time has passed since last frame
    const float dt = GameEngine::GameEngineMain::GetTimeDelta();

    //By default the displacement is 0,0
    sf::Vector2f displacement{ 0.0f,0.0f };

    //The amount of speed that we will apply when input is received
    const float inputAmount = 100.0f;

    }

    //Update the entity position
    GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
}