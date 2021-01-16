#pragma once

#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"

namespace Game
{
    class PetMovementComponent : public GameEngine::Component
    {
    public:
        PetMovementComponent();
        ~PetMovementComponent();

        virtual void Update() override;
        virtual void OnAddToWorld() override;
    private:
        GameEngine::AnimationComponent* animate;

    };
}