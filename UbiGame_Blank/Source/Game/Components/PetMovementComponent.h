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

        void SetPlayerEntity(GameEngine::Entity* player);

        virtual void Update() override;
        virtual void OnAddToWorld() override;

    private:
        GameEngine::AnimationComponent* animate;
        GameEngine::Entity* player;
        float radiusOuter;
        float radiusInner;
        bool initialState;
        bool isSitting;
    };
}