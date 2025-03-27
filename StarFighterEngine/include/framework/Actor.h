#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"
#include "framework/MathUtility.h"

class b2Body; // forward declaration

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
        sf::FloatRect GetActorGlobalBounds() const;

        sf::Vector2u GetWindowsSize() const;

        const World* GetWorld() const { return mOwningWorld; }
        World* GetWorld() { return mOwningWorld; }

        bool IsActorOutOfWindowBounds() const;

        void SetEnablePhysics(bool enable);
        virtual void OnActorBeginOverlap(Actor* other);
        virtual void OnActorEndOverlap(Actor* other);
        virtual void Destroy();

        void SetTeamID(uint8 teamID) { mTeamID = teamID; }
        static uint8 GetNeutarlTeamID() { return neutralTeamID; }
        uint8 GetTeamID() const { return mTeamID; }
        bool IsOtherHostile(Actor* other) const;
        virtual void ApplyDamage(float amount);

        const sf::Sprite& GetSprite() const { return mSprite; }
        sf::Sprite& GetSprite() { return mSprite; }

        // TODO: Implement scaling and other transformations
    private:
        void InitiallizePhysics();
        void UnInitiallizePhysics();
        void UpdatePhysicsBodyTransform();
        void UpdatePhysicsBodyRect();
        void CenterPivot();
        
        World* mOwningWorld;
        bool mHasBeganPlay;

        sf::Sprite mSprite;
        shared<sf::Texture> mTexture;
        
        b2Body* mPhysicBody; // rigid body
        sf::RectangleShape mPhysicBodyRect;
        bool mPhysicsEnabled;

        uint8 mTeamID;
        const static uint8 neutralTeamID = 255;
    };
}