/**
* @file
* ForceField.h
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
#include "TextureManager.h"
#include "CommandQueue.h"

namespace GEX {
class ForceField : public Entity
	{
	public:
		enum class Type
		{
			Bubble,
		};

	public:
		ForceField(Type type, const TextureManager& textures);

		unsigned int		getCategory() const override;
		sf::Time			getElapsedTime() const;
		sf::Time			getProtectionTime() const;
		sf::FloatRect		getBoundingBox() const;

	private:
		void				updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		Type				type_;
		sf::Sprite			sprite_;
		sf::Time			elapsedTime_;
		sf::Time			protectionTime_;
	};
}