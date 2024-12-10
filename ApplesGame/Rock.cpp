#include "Rock.h"


namespace ApplesGame
{
	void InitRock(Rock& rock, const sf::Texture& texture)
	{
		rock.position = GetRandomPositionInScreen(SCREEN_WIDTH / 0.5f, SCREEN_HEGHT / 0.5f);

		// Init sprite
		rock.sprite.setTexture(texture);
		rock.sprite.setPosition(rock.position.x, rock.position.y);
		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);
		rock.sprite.setScale(0.2f, 0.2f);
	}
	void DrawRock(Rock& rocks, sf::RenderWindow& window)
	{
		window.draw(rocks.sprite);
	}
}

