#pragma once

#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"

namespace Game
{
    class BigDogComponent : public GameEngine::Component
    {
    public:
        BigDogComponent();
        ~BigDogComponent();

        void SetHappiness(float haps);

        virtual void Update() override;
        virtual void OnAddToWorld() override;

    private:
        float happiness;
        GameEngine::AnimationComponent* animate;
        bool isDone;
    };
}