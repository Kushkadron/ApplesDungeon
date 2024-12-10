#pragma once
#include "Math.h"


namespace ApplesGame
{
	struct Apple
	{
		Position2D position;
		sf::Sprite sprite;
	};
	struct GameState;
	void InitApple(Apple& apple, const sf::Texture& texture);
	void MaxApples(Apple& apple, const sf::Texture& texture);
	void DrawApple(Apple& apple, sf::RenderWindow& window);

}
