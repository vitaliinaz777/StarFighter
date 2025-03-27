#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace st 
{
    Particle::Particle(World* owningWorld, const std::string& texturePath)
        : Actor{ owningWorld, texturePath },
        mVelocity{},
        mLifeTime{ 1.f },
        mTimer{}
    {
    }

    void Particle::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        Move(deltaTime);
        Fade(deltaTime);

        //LOG("mLifeTime: %f", mTimer.getElapsedTime().asSeconds());
        if (mTimer.getElapsedTime().asSeconds() >= mLifeTime) {
            Destroy();
        }
    }

    void Particle::RandomVelocity(float min, float max)
    {
        mVelocity = RandomUnitVector() * RandomRange(min, max);
    }

    void Particle::RandomSize(float min, float max)
    {
        float randScale = RandomRange(min, max);
        GetSprite().setScale(randScale, randScale);
    }

    void Particle::RandomLifeTime(float min, float max)
    {
        mLifeTime = RandomRange(min, max);
    }

    void Particle::Move(float deltaTime)
    {
        AddActorLocationOffset(mVelocity * deltaTime);
    }

    void Particle::Fade(float deltaTime)
    {
        float elapsedTime = mTimer.getElapsedTime().asSeconds();
        GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / mLifeTime, .5f));
        GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{0,0}, elapsedTime / mLifeTime, .5f));
    }
}