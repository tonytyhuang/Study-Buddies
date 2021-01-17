#include "PetMovementComponent.h"

#include <SFML/Window/Keyboard.hpp>   //<-- Add the keyboard include in order to get keyboard inputs
#include "GameEngine\EntitySystem\\Components\SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine/GameEngineMain.h" //<-- Add this include to retrieve the delta time between frames

using namespace Game;

float getDistance(sf::Vector2f vector) {
    float distance = abs(sqrt(vector.x * vector.x + vector.y * vector.y));
    return distance;
}

void PetMovementComponent::GetHappiness(float haps) {
    happiness = haps;
}

PetMovementComponent::PetMovementComponent() {
    initialState = true;
    radiusOuter = 400.f;
    radiusInner = 80.f;
    isSitting = false;
    happiness = 1.f;
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
    sf::Vector2f distance{ 1000.f,1000.f };
    //The amount of speed that we will apply when input is received
    const float inputAmount = 10.0f;

    if (player != nullptr) {
        distance = (player->GetPos() - GetEntity()->GetPos());
        displacement = (player->GetPos() - GetEntity()->GetPos())*dt;
    }

    if (initialState) {
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogSleep) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::DogSleep);
        }
     }
    
    if (getDistance(distance) < radiusOuter && getDistance(distance) > radiusInner && happiness > 0.3) {
        isSitting = false;
        initialState = false;
         if (abs(displacement.y) > abs(displacement.x)) {
                if (displacement.y > 0) {
                    if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogWalkDown) {
                        animate->SetIsLooping(true);
                        animate->PlayAnim(GameEngine::EAnimationId::DogWalkDown);
                    }
                }
                else {
                    if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogWalkUp) {
                        animate->SetIsLooping(true);
                        animate->PlayAnim(GameEngine::EAnimationId::DogWalkUp);
                    }
                }
            }
            else {
                if (displacement.x > 0) {
                    if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogWalkRight) {
                        animate->SetIsLooping(true);
                        animate->PlayAnim(GameEngine::EAnimationId::DogWalkRight);
                    }
                }
                else {
                    if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogWalkLeft) {
                        animate->SetIsLooping(true);
                        animate->PlayAnim(GameEngine::EAnimationId::DogWalkLeft);
                    }
                }
            }
 

            //Update the entity position
            GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
    }
    else if (getDistance(distance) <= radiusInner && happiness > 0.3) {
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogIdle && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogSit && !isSitting) {
            isSitting = true;
            animate->SetIsLooping(false);
            animate->PlayAnim(GameEngine::EAnimationId::DogSit);
        }
        else if (animate && isSitting && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogSit && animate->GetCurrentAnimation() != GameEngine::EAnimationId::DogIdle ) {
            printf("sitting");
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::DogIdle);
        }
    }

   
}

void PetMovementComponent::SetPlayerEntity(GameEngine::Entity* setPlayer) {
    player = setPlayer;
}
