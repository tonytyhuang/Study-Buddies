#include "BigDogComponent.h"

#include <SFML/Window/Keyboard.hpp>   //<-- Add the keyboard include in order to get keyboard inputs
#include "GameEngine\EntitySystem\\Components\SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine/GameEngineMain.h" //<-- Add this include to retrieve the delta time between frames

using namespace Game;

BigDogComponent::BigDogComponent() {
    isDone = false;
}

BigDogComponent::~BigDogComponent()
{

}

void BigDogComponent::SetHappiness(float haps) {
    happiness = haps;
}

void BigDogComponent::OnAddToWorld()
{
    animate = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
}

void BigDogComponent::Update() {

    if (happiness > 0.99) {
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::BigDog5) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::BigDog5);
        }
        
    }
    else if (happiness > 0.79) {
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::BigDog4) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::BigDog4);
        }
    }
    else if (happiness > 0.59) {
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::BigDog3) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::BigDog3);
        }
    }
    else if (happiness > 0.39) {
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::BigDog2) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::BigDog2);
        }
    }
    else if (happiness > 0.19) {
        if (animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::BigDog1 && !isDone) {
            isDone = true;
            animate->SetIsLooping(false);
            animate->PlayAnim(GameEngine::EAnimationId::BigDog1);
        }
        else if (isDone && animate && animate->GetCurrentAnimation() != GameEngine::EAnimationId::BigDog1 && animate->GetCurrentAnimation() != GameEngine::EAnimationId::BigDog0) {
            animate->SetIsLooping(true);
            animate->PlayAnim(GameEngine::EAnimationId::BigDog0);
        }
    }

}