#include "Apple.h"

namespace ApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		// init apple state
		apple.position = GetRandomPositionInScreen(SCREEN_WIDTH / 1.f, SCREEN_HEGHT / 1.f);

		// Init sprite
		apple.sprite.setTexture(texture);
		apple.sprite.setPosition({apple.position.x, apple.position.y });
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
		apple.sprite.setScale(0.08f, 0.08f);
	}

	//дл€ конечного режима решила сделать новую функцию, котора€ заменит numEatenApples на старте, чтобы вместо 0 €блок было 20
	void MaxApples(Apple& apple, const sf::Texture& texture)
	{
		int remainingApples = 20;
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		window.draw(apple.sprite);
	}

}
