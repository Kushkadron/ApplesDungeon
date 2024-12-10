#pragma once
#include "Math.h"


namespace ApplesGame
{
	
	struct Rock
	{
		Position2D position;
		sf::Sprite sprite;
	};
	struct GameState;
	void InitRock(Rock& rocks, const sf::Texture& texture);
	void DrawRock(Rock& rocks, sf::RenderWindow& window);
}

