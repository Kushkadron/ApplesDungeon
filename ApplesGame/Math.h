#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	typedef Vector2D Position2D;

	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);
	bool IsRectanglesCollide(Position2D rect1Position, Position2D rect1Size, Position2D rect2Position, Position2D rect2Size);
	bool IsCirclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	int Get_Random_Int(const int& min, const int& max);
	//sf::Vector2f OurVectorToSf(const Position2D& v);
	//sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Position2D& desiredSize);
	//sf::Vector2f GetSpriteOrigin(const sf::Sprite& sprite, const Position2D& relativePosition);
	//sf::Vector2f GetTextOrigin(const sf::Text& text, const Position2D& relativePosition);
}
