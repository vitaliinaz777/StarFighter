#pragma once
#include "framework/Actor.h"

namespace st 
{
    class Particle : public Actor
    {
    public:
        Particle(World* owningWorld, const std::string& texturePath);
        virtual void Tick(float deltaTime) override;

        void RandomVelocity(float min, float max);
        void RandomSize(float min, float max);
        void RandomLifeTime(float min, float max);

    private:
        void Move(float deltaTime);
        void Fade(float deltaTime);

        sf::Vector2f mVelocity;
        float mLifeTime;
        sf::Clock mTimer;
    };
}