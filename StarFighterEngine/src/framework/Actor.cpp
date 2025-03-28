#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
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
        mPhysicBody{ nullptr }, 
        mPhysicBodyRect{},
        mPhysicsEnabled{ false },
        mTeamID{ GetNeutarlTeamID()}
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        //LOG("Actor destroyed");
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
        //LOG("Actor::BeginPlay");
    }

    void Actor::Tick(float deltaTime)
    {
        //LOG("Actor::Tick");
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        mTexture = AssetManager::Get().LoadTexture(texturePath);
        if (!mTexture) return; // if the texture is not loaded, return
        mSprite.setTexture(*mTexture, true);

        //int textureWidth = mTexture->getSize().x;
        //int textureHeight = mTexture->getSize().y;
        //mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight } });
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow& window)
    {
        // don't drow if pending for destroy
        if (IsPendingDestroy()) {
            return;
        }

        window.draw(mSprite);
        window.draw(mPhysicBodyRect);
    }

    void Actor::SetActorLocation(const sf::Vector2f& newLoc)
    {
        mSprite.setPosition(newLoc);
        UpdatePhysicsBodyTransform();
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
    {
        //mSprite.move(offsetAmt);
        SetActorLocation(GetActorLocation() + offsetAmt);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite.getPosition();
    }

    void Actor::SetActorRotation(float newRotation)
    {
        mSprite.setRotation(newRotation);
        UpdatePhysicsBodyTransform();
    }

    void Actor::AddActorRotationOffset(float offsetAmt)
    {
        //mSprite.rotate(offsetAmt);
        SetActorRotation(GetActorRotation() + offsetAmt);
    }

    float Actor::GetActorRotation() const
    {
        return mSprite.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDirection() const
    {
        return RotationToVector(GetActorRotation());
    }

    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return RotationToVector(GetActorRotation() + 90.0f);
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return mSprite.getGlobalBounds();
    }

    sf::Vector2u Actor::GetWindowsSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    bool Actor::IsActorOutOfWindowBounds(float allowance) const
    {
        // 'allowance' allows the Actor to move beyond the screen before being destroyed
                 
        float windowWidth = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float width = GetActorGlobalBounds().width;
        float height = GetActorGlobalBounds().height;

        sf::Vector2f actorPos = GetActorLocation();

        if (actorPos.x < -width - allowance) {
            return true;
        }

        if (actorPos.x > windowWidth + width + allowance) {
            return true;
        }

        if (actorPos.y < -height - allowance) {
            return true;
        }

        if (actorPos.y > windowHeight + height + allowance) {
            return true;
        }

        return false;
    }

    void Actor::SetEnablePhysics(bool enable)
    {
        mPhysicsEnabled = enable;
        if (mPhysicsEnabled) {
            InitiallizePhysics();
        } else {
            UnInitiallizePhysics();
        }
    }

    void Actor::OnActorBeginOverlap(Actor* other)
    {
        //LOG("Overlapped");
    }

    void Actor::OnActorEndOverlap(Actor* other)
    {
        //LOG("Overlap finished");
    }

    void Actor::Destroy()
    {
        UnInitiallizePhysics();
        Object::Destroy();
    }

    bool Actor::IsOtherHostile(Actor* other) const
    {
        if (other == nullptr) return false;

        // if any of two is netural
        if (GetTeamID() == GetNeutarlTeamID() || other->GetTeamID() == GetNeutarlTeamID()) {
            return false; // we are not enemies
        }

        return GetTeamID() != other->GetTeamID();
    }

    void Actor::InitiallizePhysics()
    {
        if (!mPhysicBody) {
            mPhysicBody = PhysicsSystem::Get().AddListener(this);
        }
    }

    // Delete ridgid body
    void Actor::UnInitiallizePhysics()
    {
        if (mPhysicBody) {
            PhysicsSystem::Get().RemoveListener(mPhysicBody);
            mPhysicBody = nullptr;
        }
    }

    void Actor::UpdatePhysicsBodyTransform()
    {
        if (mPhysicBody) {
            float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 pos{ GetActorLocation().x * physicsScale, 
                        GetActorLocation().y * physicsScale };
            float rotation = DegreesToRadians(GetActorRotation());

            mPhysicBody->SetTransform(pos, rotation);

            UpdatePhysicsBodyRect();
        }
    }

    void Actor::UpdatePhysicsBodyRect()
    {
        float physicsScale = 1 / PhysicsSystem::Get().GetPhysicsScale();

        // size
        Actor* actor = reinterpret_cast<Actor*>(mPhysicBody->GetUserData().pointer);
        mPhysicBodyRect.setSize(sf::Vector2f(actor->mSprite.getTextureRect().width,
                                             actor->mSprite.getTextureRect().height));

        // color
        mPhysicBodyRect.setOutlineColor(sf::Color::Red);
        mPhysicBodyRect.setFillColor(sf::Color::Transparent);

        // thikness
        mPhysicBodyRect.setOutlineThickness(1.f);

        // position
        mPhysicBodyRect.setPosition(sf::Vector2f{ mPhysicBody->GetPosition().x * physicsScale,
                                                  mPhysicBody->GetPosition().y * physicsScale });

        // rotation
        mPhysicBodyRect.setRotation(RadiansToDegrees(mPhysicBody->GetAngle()));

        // origin
        sf::FloatRect bounds = actor->mSprite.getLocalBounds();
        mPhysicBodyRect.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
    }

    void Actor::ApplyDamage(float amount) {

    }
}