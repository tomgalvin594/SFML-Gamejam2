#include "positionTracker.hpp"

#include <SFML/System/Time.hpp>

#include <iostream>

namespace aw
{
	void PositionTracker::update(const sf::Time &frameTime, sf::Vector2f position, sf::Vector2f velocity)
	{
		mSinceLastSave += frameTime;

		if (mSinceLastSave > mBetweenSaves)
		{
			mSinceLastSave -= mBetweenSaves;
			std::array<sf::Vector2f, 2> temp = { sf::Vector2f(position.x, position.y - 0.5f), velocity };
			mPastPositions.push_back(temp);
			if (mPastPositions.size() > static_cast<unsigned int>(2.5f / mBetweenSaves.asSeconds()))
			{
				mPastPositions.pop_front();
			}
		}
	}

	void PositionTracker::startGoingBackInTime(sf::Vector2f position, sf::Vector2f velocity)
	{
		std::array<sf::Vector2f, 2> temp = { position, velocity };
		mPastPositions.push_back(temp);
		mPercentage = 0;
	}

	std::array<sf::Vector2f, 2> PositionTracker::goingBack(const sf::Time &frameTime)
	{
		if (mPastPositions.size() == 1)
		{
			return mPastPositions.back();
		}
		else
		{
			//Calculate new percentage
			mPercentage += frameTime / mBetweenSaves;
			if (mPercentage < 1.f)
			{
				//Get dir vector (Last point to -1last point
				auto it = mPastPositions.rbegin()++;
				sf::Vector2f dir = it->at(0) - mPastPositions.back()[0];
				//Get final position
				sf::Vector2f newPosition = mPastPositions.back()[0] + (mPercentage * dir);
				//Same for velocity (interpolation
				sf::Vector2f vel = it->at(1) - mPastPositions.back()[1];
				//Get final velocity
				sf::Vector2f newVelocity = mPastPositions.back()[1] + (mPercentage * vel);
				std::array<sf::Vector2f, 2> returnValue = { newPosition, newVelocity };
				return returnValue;
			}
			else
			{
				mPercentage = 0.f;
				mPastPositions.pop_back();
				std::array<sf::Vector2f, 2> newValues = mPastPositions.back();
				return newValues;
			}
		}
	}
}