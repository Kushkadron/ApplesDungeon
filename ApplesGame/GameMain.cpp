// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include "Game.h"

using namespace ApplesGame;

void HandleWindowEvents(sf::RenderWindow& window, GameState& gameState)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Закрытие окна при нажатии кнопки азакрытия или эскейп
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}
		HandleInputCheck(gameState,window, event);
	}
}

int main()
{
	// Init random number generator
	unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(ApplesGame::SCREEN_WIDTH, ApplesGame::SCREEN_HEGHT), "AppleGame");
	ApplesGame::GameState gameState;
	InitGame(gameState);

	// Init game clock
	sf::Clock game_clock;
	sf::Time lastTime = game_clock.getElapsedTime();

	// Цикличность игры
	while (window.isOpen())
	{
		HandleWindowEvents(window, gameState);

		if (!window.isOpen())
		{
			return 0;
		}

		HandleInputMove(gameState);

		// Calculate time delta
		sf::Time currentTime = game_clock.getElapsedTime();
		float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
		lastTime = currentTime;
		UpdateGame(gameState, timeDelta);


		// Draw everything here
		// Clear the window first
		window.clear();

		DrawGame(gameState, window);

		// End the current frame, display window contents on screen
		window.display();
	}

	return 0;
}
