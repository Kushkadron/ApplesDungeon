#pragma once
#include "Math.h"



namespace ApplesGame
{
	enum class PlayerDirection
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	
	struct Player
	{
		Position2D position;
		float speed = 0.f;
		PlayerDirection direction = PlayerDirection::Up;
		sf::Sprite sprite;
	};
	struct GameState;
	struct Apple;
	void InitPlayer(Player& player, const sf::Texture& texture);
	void UpdatePlayer(Player& player, float timeDelta);

	bool HasPlayerCollisionWithScreenBorder(const Player& player);
	bool HasPlayerCollisionWithObject(const Player& player, const Position2D& position, const float ObjectSize);

	void DrawPlayer(Player& player, sf::RenderWindow& window);

}
