#include "PetMovementComponent.h"

#include <SFML/Window/Keyboard.hpp>   //<-- Add the keyboard include in order to get keyboard inputs
#include "GameEngine\EntitySystem\\Components\SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine/GameEngineMain.h" //<-- Add this include to retrieve the delta time between frames

using namespace Game;

PetMovementComponent::PetMovementComponent() {

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
    const float inputAmount = 10.0f;
    if (player != nullptr) {
        
        displacement = (player->GetPos() - GetEntity()->GetPos())*dt;
    }
    if (abs(displacement.y) > abs(displacement.x)) {
        if (displacement.y > 0) {

        }
        else {

        }
    }
    
    if(animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogIdle)
    {
        animate->SetIsLooping(true);
        animate->PlayAnim(GameEngine::EAnimationId::DogIdle);
    }

    //Update the entity position
    GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
}

void PetMovementComponent::SetPlayerEntity(GameEngine::Entity* setPlayer) {
    player = setPlayer;
}