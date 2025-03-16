#include <box2d/b2_body.h>
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"
#include "framework/PhysicsSystem.h"
#include "framework/World.h" 

namespace st
{
    Actor::Actor(World* owningWorld, const std::string& texturePath)
        : mOwningWorld{ owningWorld },
        mHasBeganPlay{ false },
        mSprite{},
        mTexture{},
        mPhysicBody{nullptr}, 
        mPhysicsEnabled{false}
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        LOG("Actor destroyed");
    }

    void Actor::BeginPlayInternal()
    {
        if (!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();

        }
    }

    void Actor::TickInternal(float deltaTime)
    {
        if (!IsPendingDestroy()) {
            Tick(deltaTime);
        }
    }

    void Actor::BeginPlay()
    {
        LOG("Actor::BeginPlay");
    }

    void Actor::Tick(float deltaTime)
    {
        //LOG("Actor::Tick");
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        mTexture = AssetManager::Get().LoadTexture(texturePath);
        if (!mTexture) return; // if the texture is not loaded, return
        mSprite.setTexture(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight } });
        CenterPivot();
    }
}

void st::Actor::Render(sf::RenderWindow& window)
{
    // don't drow if pending for destroy
    if (IsPendingDestroy()) {
        return;
    }

    window.draw(mSprite);
}

void st::Actor::SetActorLocation(const sf::Vector2f& newLoc)
{
    mSprite.setPosition(newLoc);
}

void st::Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
{
    //mSprite.move(offsetAmt);
    SetActorLocation(GetActorLocation() + offsetAmt);
}

sf::Vector2f st::Actor::GetActorLocation() const
{
    return mSprite.getPosition();
}

void st::Actor::SetActorRotation(float NewRotation)
{
    mSprite.setRotation(NewRotation);
}

void st::Actor::AddActorRotationOffset(float offsetAmt)
{
    //mSprite.rotate(offsetAmt);
    SetActorRotation(GetActorRotation() + offsetAmt);
}

float st::Actor::GetActorRotation() const
{
    return mSprite.getRotation();
}

sf::Vector2f st::Actor::GetActorForwardDirection() const
{
    return RotationToVector(GetActorRotation());
}

sf::Vector2f st::Actor::GetActorRightDirection() const
{
    return RotationToVector(GetActorRotation() + 90.0f);
}

sf::FloatRect st::Actor::GetActorGlobalBounds() const
{
    return mSprite.getGlobalBounds();
}

sf::Vector2u st::Actor::GetWindowsSize() const
{
    return mOwningWorld->GetWindowSize();
}

bool st::Actor::IsActorOutOfWindowBounds() const
{
    float windowWidth = GetWorld()->GetWindowSize().x;
    float windowHeight = GetWorld()->GetWindowSize().y;

    float width = GetActorGlobalBounds().width;
    float height = GetActorGlobalBounds().height;

    sf::Vector2f actorPos = GetActorLocation();

    if (actorPos.x < -width) {
        return true;
    }

    if (actorPos.x > windowWidth + width) {
        return true;
    }

    if (actorPos.y > windowHeight + height) {
        return true;
    }

    if (actorPos.y < -height) {
        return true;
    }

    return false;
}

void st::Actor::SetEnablePhysics(bool enable)
{
    mPhysicsEnabled = enable;
    if (mPhysicsEnabled) {
        InitiallizePhysics();
    }
    else {
        UnInitiallizePhysics();
    }
}

void st::Actor::InitiallizePhysics()
{
    if (!mPhysicBody) {
        mPhysicBody = PhysicsSystem::Get().AddListener(this);
    }
}

void st::Actor::UnInitiallizePhysics()
{
    if (mPhysicBody) {
        PhysicsSystem::Get().RemoveListener(mPhysicBody);
    }
}

void st::Actor::UpdatePhysicsBodyTransform()
{
    if (mPhysicBody) {
        float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
        b2Vec2 pos{GetActorLocation().x * physicsScale,
                   GetActorLocation().y * physicsScale};
        float rotation = DegreesToRadians(GetActorRotation());

        mPhysicBody->SetTransform(pos, rotation);
    }
}

void st::Actor::CenterPivot()
{
    sf::FloatRect bound = mSprite.getGlobalBounds();
    mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
}
