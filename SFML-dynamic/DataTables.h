/**
* @file
* DataTables.h
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
#pragma once
#include "TextureManager.h"
#include "Aircraft.h"
#include <map>
#include "Projectile.h"
#include "Pickup.h"
#include "Particle.h"
#include "Animation2.h"
#include "Actor.h"
#include "ForceField.h"

namespace GEX
{
	struct Direction
	{
		Direction(float a, float d) 
			: angle(a)
			, distance(d) 
		{}

		float	angle;
		float	distance;
	};

	struct AircraftData
	{
		int										hitpoints;
		float									speed;
		TextureID								texture;
		sf::IntRect								textureRect;
		sf::Time								fireInterval;
		int										missileAmount;
		bool									hasRollAnimation;

		std::vector<Direction>					directions;
	};

	struct ProjectileData
	{
		int										damage;
		float									speed;
		TextureID								texture;
		sf::IntRect								textureRect;
	};

	struct PickupData
	{
		std::function<void(Aircraft&)>			action;
		TextureID								texture;
		sf::IntRect								textureRect;
	};

	struct ParticleData
	{
		sf::Color								color;
		sf::Time								lifetime;
	};

	struct ActorData
	{
		int										hitpoints;
		int										damageDone;
		float									speed;
		bool									follows;
		bool									forcefield;
		bool									godMode;
		sf::Time								godModeTime;
		TextureID								texture;
		std::map<Actor::State, Animation2>		animations;

		std::vector<Direction>					directions;
	};

	struct ForceFieldData
	{
		TextureID								texture;
		sf::IntRect								textureRect;
		sf::Time								protectionTime;
	};

	std::map<ActorType, ActorData>				initializeActorData();

	std::map<AircraftType, AircraftData>		initializeAircraftData();
	std::map<Projectile::Type, ProjectileData>	initializeProjectileData();
	std::map<Pickup::Type, PickupData>			initializePickupData();
	std::map<Particle::Type, ParticleData>		initializeParticleData();
	std::map<ForceField::Type, ForceFieldData>	initializeForceFieldData();
}
