/**
* @file
* Actor.h
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
#include "Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include "TextureManager.h"
#include "Command.h"

namespace GEX
{
	class CommandQueue;
	class TextNode;

	//Types of aircraft
	enum class ActorType { Zombie, Hero };

	class Actor : public Entity
	{
	public:
		/*Actor();
		virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

		unsigned int	getCategory() const override;

		sf::FloatRect	getBoundingBox() const override;

		bool			isMarkedForRemoval() const override;

		void			remove();

	protected:
		void			updateCurrent(sf::Time dt, CommandQueue& commands) override;

	private:
		void			updateMovementPattern(sf::Time dt);

	private:
		ActorType		type_;
		sf::Sprite		sprite_;
		bool			isMarkedForRemoval_;*/
	};
}

