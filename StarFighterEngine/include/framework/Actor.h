#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"


namespace st
{
    class World; // forward declaration

    // Base class for all actors in the game
    class Actor : public Object
    {
    public:
        Actor(World* owningWorld, const std::string& texturePath = "");
        virtual ~Actor();

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

        void SetTexture(const std::string& texturePath);
        void Render(sf::RenderWindow& window);

        void SetActorLocation(const sf::Vector2f& newLoc);
        void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
        sf::Vector2f GetActorLocation() const;

        void SetActorRotation(float NewRotation);
        void AddActorRotationOffset(float offsetAmt);
        float GetActorRotation() const;

        sf::Vector2f GetActorForwardDirection() const;
        sf::Vector2f GetActorRightDirection() const;

        sf::Vector2u GetWindowsSize() const;

        // TODO: Implement scaling and other transformations

    private:
        void CenterPivot();
        World* mOwningWorld;
        bool mHasBeganPlay;

        sf::Sprite mSprite;
        shared<sf::Texture> mTexture;
    };
}