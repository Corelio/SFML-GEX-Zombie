/**
* @file
* Actor.cpp
* @author
* Marco Corsini Baccaro 2018
* @version 1.0
*
* @section DESCRIPTION
* Assignment #1 - The GexState (Oct, 8th)
*
* @section LICENSE
*
* Copyright 2018
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/
#include "Actor.h"
#include "TextureManager.h"
#include "JsonFrameParser.h"
#include "TextureManager.h"
#include "Utility.h"
#include "DataTables.h"
#include "TextNode.h"

namespace GEX
{
	namespace
	{
		const std::map<ActorType, ActorData> TABLE = initializeActorData();
	}

	Actor::Actor(ActorType type, const GEX::TextureManager& textures)
		: Entity(100)
		, type_(type)
		, state_(State::Walk)
		, sprite_(textures.get(TABLE.at(type).texture))
		, direction_(Direction::Right)
		, travelDistance_(0.f)
		, directionIndex_(0)
		, attack_(false)

	{
		for (auto a : TABLE.at(type).animations)
		{
			animations_[a.first] = a.second;
		}

		if (Actor::getCategory() == Category::Zombie)
			state_ = State::Rise;  // zombies spawn in rise state

		centerOrigin(sprite_);

		//
		// set up text for health and missiles
		// 
		std::unique_ptr<TextNode> health(new TextNode(""));
		healthDisplay_ = health.get();
		attachChild(std::move(health));

		updateTexts();
	}



	unsigned int Actor::getCategory() const
	{
		switch (type_)
		{
		case ActorType::Hero2:
			return Category::Hero;
			break;
		case ActorType::Zombie1:
		case ActorType::Zombie2:
		case ActorType::Zombie3:
		case ActorType::Zombie4:
			return Category::Zombie;
			break;
		}
	}

	void Actor::updateMovementPattern(sf::Time dt)
	{
		// movement pattern
		const std::vector<GEX::Direction> directions = TABLE.at(type_).directions;

		if (!directions.empty())
		{
			if (travelDistance_ > (directions[directionIndex_].distance))
			{
				directionIndex_ = (++directionIndex_) % directions.size();
				travelDistance_ = 0;
			}

			float radians = toRadian(directions[directionIndex_].angle + 90.f);
			float vx = getMaxSpeed() * std::cos(radians);
			float vy = getMaxSpeed() * std::sin(radians);

			setVelocity(vx, vy);
			travelDistance_ += getMaxSpeed() * dt.asSeconds();
		}
	}

	sf::FloatRect Actor::getBoundingBox() const
	{
		auto box = getWorldTransform().transformRect(sprite_.getGlobalBounds());
		box.width -= 30; // tighten up bounding box for more realistic collisions
		box.left += 15;
		return box;
	}

	float Actor::getMaxSpeed() const
	{
		return TABLE.at(type_).speed;
	}

	void Actor::accelerate(sf::Vector2f velocity)
	{
		switch (state_)
		{
		case State::Attack:
			Entity::accelerate(velocity / 4.f);
			break;
		case State::Walk:
			Entity::accelerate(velocity);
			break;
		case State::Run:
			Entity::accelerate(velocity * 2.f);
		}
	}

	void Actor::attack()
	{
		attack_ = true;
	}

	void Actor::setState(State state)
	{
		state_ = state;
		animations_[state_].restart();
	}

	int Actor::attackPoints() const
	{
		if (type_ == ActorType::Hero2 && state_ == State::Attack)
			return TABLE.at(type_).damageDone;
		else if (type_ != ActorType::Hero2)
			return TABLE.at(type_).damageDone;
		else
			return 0;
	}


	void Actor::updateStates()
	{
		if (state_ == State::Attack && animations_[state_].isFinished())
			state_ = State::Walk;

		if (attack_ && state_ != State::Attack)
		{
			state_ = State::Attack;
			animations_[state_].restart();
			attack_ = false;
		}

		if (state_ == State::Rise && animations_[state_].isFinished())
			state_ = State::Idle;

		if (state_ == State::Idle && length(getVelocity()) > 0.1f)
			state_ = State::Walk;

		if (isDestroyed()) {
			state_ = State::Dead;
		}
	}

	void Actor::updateCurrent(sf::Time dt, GEX::CommandQueue & commands)
	{
		updateStates();

		auto rec = animations_.at(state_).update(dt);

		if (direction_ == Direction::Left && getVelocity().x > 10)
			direction_ = Direction::Right;
		if (direction_ == Direction::Right && getVelocity().x < 0)
			direction_ = Direction::Left;

		// flip image left right
		if (direction_ == Direction::Left)
			rec = flip(rec);

		sprite_.setTextureRect(rec);
		centerOrigin(sprite_);

		if (state_ != State::Dead) // dont move it while dying
			Entity::updateCurrent(dt, commands);

		updateMovementPattern(dt);
		updateTexts();
	}

	void Actor::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}

	void Actor::updateTexts()
	{
		healthDisplay_->setText(std::to_string(getHitpoints()) + "HP");
		healthDisplay_->setPosition(0.f, 70.f);
		healthDisplay_->setRotation(-getRotation());
	}

	bool Actor::isMarkedForRemoval() const
	{
		return isDestroyed() && animations_[state_].isFinished();
	}
}
