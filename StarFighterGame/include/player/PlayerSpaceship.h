#pragma once
#include "spaceship/Spaceship.h"

namespace st
{
    // forward declaration
    class BulletShooter;

    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
        ~PlayerSpaceship(); // to resolve pimpl problem 

        virtual void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
        float GetSpeed() const { return mSpeed; }
        virtual void Shoot() override;
    private:
        void HandleInput();
        void NormalizeInput();
        void ClampInputOnEdge();
        void ConsumeInput(float deltaTime);  // consume the input 
        // and set the velocity of the spaceship
        sf::Vector2f mMoveInput; // direction
        float mSpeed;

        unique<BulletShooter> mShooter;
    };
}