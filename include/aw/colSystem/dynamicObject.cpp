#include "dynamicObject.hpp"

#include <iostream>

#include <SFML/System/Time.hpp>

#include "collisionLine.hpp"

namespace aw
{
	namespace col
	{
		DynamicObject::DynamicObject() :
			DynamicObject(sf::Vector2f(), sf::Vector2f())
		{

		}

		DynamicObject::DynamicObject(const sf::Vector2f &position, const sf::Vector2f &size) :
			mState(DynamicState::FALLING),
			mPosition(position),
			mLastPosition(position),
			mSize(size),
			mVelocity(0,0),
			mBoundLine(nullptr),
			mCollisionImmune(false),
			mAlive(true)
		{

		}

		void DynamicObject::updatePosition(const sf::Time &deltaTime)
		{
			//Save the current (old) position
			//Need by the collision System
			mLastPosition = mPosition;
			//Calculate the new one
			mPosition += mVelocity * deltaTime.asSeconds();
		}

		void DynamicObject::setPosition(const sf::Vector2f &position)
		{
			mPosition = position;
			updatePosition(sf::Time::Zero);
		}

		void DynamicObject::setLastPosition(const sf::Vector2f &position)
		{
			mLastPosition = position;
		}
		
		void DynamicObject::setSize(const sf::Vector2f &size)
		{
			mSize = size;
		}

		void DynamicObject::setVelocity(const sf::Vector2f &velocity)
		{
			mVelocity = velocity;
		}

		void DynamicObject::changeVelocity(const sf::Vector2f &value)
		{
			mVelocity += value;
		}

		void DynamicObject::setBoundLine(CollisionLine *ptr)
		{
			mBoundLine = ptr;

			if (mBoundLine)
				changeState(DynamicState::ON_GROUND);
			else
				changeState(DynamicState::FALLING);
		}

		void DynamicObject::setCollisionImmune()
		{
			mCollisionImmune = true;
		}

		void DynamicObject::setAlive(bool val)
		{
			mAlive = val;
		}

		const sf::Vector2f &DynamicObject::getPosition() const
		{
			return mPosition;
		}

		const sf::Vector2f &DynamicObject::getLastPosition() const
		{
			return mLastPosition;
		}

		const sf::Vector2f &DynamicObject::getSize() const
		{
			return mSize;
		}

		const sf::Vector2f &DynamicObject::getVelocity() const
		{
			return mVelocity;
		}

		const CollisionLine *DynamicObject::getBoundLine() const
		{
			return mBoundLine;
		}

		DynamicState DynamicObject::getState() const
		{
			return mState;
		}

		bool DynamicObject::getImmune()
		{
			if (mCollisionImmune)
			{
				mCollisionImmune = false;
				return true;
			}
			return mCollisionImmune;
		}

		bool DynamicObject::isAlive() const
		{
			return mAlive;
		}

		void DynamicObject::changeState(DynamicState newState)
		{
			mState = newState;

			//std::cout << "Changed state to: ";

			switch (mState)
			{
			case DynamicState::FALLING: std::cout << "FALLING"; break;
			case DynamicState::ON_GROUND: std::cout << "ON_GROUND"; break;
			default: break;
			}

			std::cout << std::endl;
		}
	}
}