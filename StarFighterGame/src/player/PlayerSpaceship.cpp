#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"

namespace st
{
    PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
        : Spaceship{ owningWorld, path },
        mMoveInput{ 0.f, 0.f },
        mSpeed{ 200.f },
        mShooter{ new BulletShooter{this, 0.1f, {50.f, 0.f}} }
    {
        SetTeamID(1);
    }

    // TODO: added destructor to resolve pimpl problem with nique<BulletShooter> mShooter
    PlayerSpaceship::~PlayerSpaceship()
    {
        LOG("PlayerSpaceship destroyed :`(");
    };

    void PlayerSpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
    }

    void PlayerSpaceship::Shoot()
    {
        if (mShooter) {
            mShooter->Shoot();
        }
    }

    void PlayerSpaceship::HandleInput()
    {
        // Handle vertical movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            mMoveInput.y = -1.f; // up
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            mMoveInput.y = 1.f; // down
        }

        // Handle horizontal movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            mMoveInput.x = -1.f; // left
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            mMoveInput.x = 1.f; // right
        }

        ClampInputOnEdge();
        NormalizeInput();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            Shoot();
        }
    }

    void PlayerSpaceship::NormalizeInput()
    {
        Normalize(mMoveInput);
        //LOG("Normalized input: %f, %f", mMoveInput.x, mMoveInput.y);
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2f actorLocation = GetActorLocation();
        if (actorLocation.x < 0.f && mMoveInput.x == -1) {
            mMoveInput.x = 0.f;
        }

        if (actorLocation.x > GetWindowsSize().x && mMoveInput.x == 1.f) {
            mMoveInput.x = 0.f;
        }

        if (actorLocation.y < 0.f && mMoveInput.y == -1) {
            mMoveInput.y = 0.f;
        }

        if (actorLocation.y > GetWindowsSize().y && mMoveInput.y == 1.f) {
            mMoveInput.y = 0.f;
        }
    }

    // Consume the input and set the velocity of the spaceship
    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);

        // reset the input
        mMoveInput.x = 0.f;
        mMoveInput.y = 0.f;
    }
}
