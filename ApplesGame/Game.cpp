#include "Game.h"
#include <assert.h>


namespace ApplesGame
{
	void InitGame(GameState& gameState)
	{
		// Init game resources (terminate if error)
		assert (gameState.font.loadFromFile(RESOURCES_PATH + "Fonts/SkrampCyr-Regular_0.ttf"));
		assert (gameState.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert (gameState.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(gameState.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));
		assert(gameState.eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(gameState.GameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));
		assert (gameState.menuTexture.loadFromFile(RESOURCES_PATH + "background.png"));

		gameState.menuSprite.setTexture(gameState.menuTexture);
		gameState.appleEatSound.setBuffer(gameState.eatAppleSoundBuffer);
		gameState.deathSound.setBuffer(gameState.GameOverSoundBuffer);
		
		// Мод игры - меню
		SetGameMode(gameState, gameState.MenuState);
		SetGameMode(gameState, END_MODE);

		InitUI(gameState.uiState, gameState.font);
		RestartGame(gameState);
	}

	void RestartGame(GameState& gameState)
	{
		if (!gameState.AppleVector.empty())
		{
			gameState.AppleVector.clear();
		}
		// Init player
		InitPlayer(gameState.player, gameState.playerTexture);
		// Init apples
		for (int i = 0; i < NUM_APPLES; i++)
		{
			Apple appleobj;
			gameState.AppleVector.push_back(appleobj);
			InitApple(gameState.AppleVector[i], gameState.appleTexture);
		}
		// Init rocks
		for (int i = 0; i < NUM_ROCKS; i++)
		{
			InitRock(gameState.rocks[i], gameState.rockTexture);
		}
		// Init game state
		gameState.numEatenApples = 0;
		gameState.timeSinceGameOver = 0.f;

		//if (gamestate.gamemode & gamestate.menustate)
		//{
		//	gamestate.gamemode = gamestate.menustate;
		//}
		//else if (gamestate.gamemode & gamestate.playingstate)
		//{
		//	gamestate.gamemode = gamestate.playingstate;
		//}


	}

	void HandleInputMove(GameState& gameState)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gameState.player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameState.player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gameState.player.direction = PlayerDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameState.player.direction = PlayerDirection::Left;
		}
	}

	void UpdateGame(GameState& gameState, float timeDelta)
	{
		if (CheckGameMode(gameState, gameState.PlayingState))
		{
			// Обновить игрока
			UpdatePlayer(gameState.player, timeDelta);

			std::vector<int> RemoveApples; 

			for (int i = 0; i < gameState.AppleVector.size(); ++i)
			{
				Apple& apple = gameState.AppleVector[i];
				// Проверка столкновения с яблоком
				if (HasPlayerCollisionWithObject(gameState.player, apple.position, APPLE_SIZE))
				{
					// Увеличиваем счетчик съеденных яблок
					gameState.numEatenApples++;
					// Проигрываем звук съедания яблока
					gameState.appleEatSound.play();

					//Удаляем яблоко из вектора
					gameState.AppleVector.erase(gameState.AppleVector.begin() + i);

					if (CheckGameMode(gameState, INFINITE_MODE))
					{
						// Переместить яблоко в новую случайную позицию
						InitApple(apple, gameState.appleTexture);
					}
					else if (CheckGameMode(gameState, END_MODE))
					{
						if (gameState.numEatenApples == NUM_APPLES)
						{
							ToggleGameMode(gameState, gameState.PlayingState);
							SetGameMode(gameState, gameState.GameOverState);
						}
					}
					if (CheckGameMode(gameState, ACCELERATION_MODE))
					{
						gameState.player.speed += ACCELERATION;
					}
				}
			}
			for (auto apple = RemoveApples.rbegin(); apple != RemoveApples.rend(); ++apple)
			{
				gameState.AppleVector.erase(gameState.AppleVector.begin() + (*apple));
			}
			/*for (auto& apple : RemoveApples)
			{
				gameState.AppleVector.erase(gameState.AppleVector.begin() + *(apple));
			}*/

			for (int i = 0; i < NUM_ROCKS; i++)
			{
				// Проверить коллизии камней
				if (HasPlayerCollisionWithObject(gameState.player, gameState.rocks[i].position, ROCK_SIZE))
				{
					// Новая рандомная позиция камня
					//Переключаем бит playing на 0
					gameState.player.speed = 0;
					ToggleGameMode(gameState, gameState.PlayingState);
					SetGameMode(gameState, gameState.GameOverState);
					gameState.deathSound.play();
				}
			}
				// Коллизии с экраном
			if (HasPlayerCollisionWithScreenBorder(gameState.player))
			{
				//Переключаем бит playing на 0
				ToggleGameMode(gameState, gameState.PlayingState);
				SetGameMode(gameState, gameState.GameOverState);
				gameState.player.speed = 0;
				gameState.timeSinceGameOver = 0.f;
				gameState.deathSound.play();
			}
		}
		else
		{
			gameState.timeSinceGameOver += timeDelta;
		}

		UpdateUI(gameState.uiState, gameState, timeDelta);
	}

	void HandleInputCheck(GameState& gameState, sf::RenderWindow& window, sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			if (CheckGameMode(gameState, gameState.MenuState))
			{
				ToggleGameMode(gameState, gameState.MenuState);
				SetGameMode(gameState, gameState.PlayingState);

			}
 			else if (CheckGameMode(gameState, gameState.GameOverState))
			{
				ToggleGameMode(gameState, gameState.GameOverState);
				SetGameMode(gameState, gameState.MenuState);
				RestartGame(gameState);
			}
			
		}

		//Включение/выключение ускорения
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
		{
			ToggleGameMode(gameState, ACCELERATION_MODE);
			GetModeText(gameState, ACCELERATION_MODE);
		}
		//Обычный (конечный) режим
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard:: Num2)
		{
			ToggleGameMode(gameState, END_MODE);
			GetModeText(gameState, END_MODE);
			ToggleGameMode(gameState, INFINITE_MODE);
			GetModeText(gameState, INFINITE_MODE);
		}
		//Бесконечный
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard:: Num3)
		{
			ToggleGameMode(gameState, INFINITE_MODE);
			GetModeText(gameState, INFINITE_MODE);
			ToggleGameMode(gameState, END_MODE);
			GetModeText(gameState, END_MODE);
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
		{
			if (CheckGameMode(gameState, gameState.PlayingState))
			{
				ToggleGameMode(gameState, gameState.PlayingState);
				SetGameMode(gameState, gameState.PauseState);
			}
		}
		//Позиция мышки в меню
		gameState.MousePosition = sf::Mouse::getPosition(window);

		if (gameState.uiState.continueText.getGlobalBounds().contains(gameState.MousePosition.x, gameState.MousePosition.y))
		{
			gameState.uiState.continueText.setFillColor(sf::Color::Yellow);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				ToggleGameMode(gameState, gameState.PauseState);
				SetGameMode(gameState, gameState.PlayingState);
			}
		}
		else
		{
			gameState.uiState.continueText.setFillColor(sf::Color::White);
		}
		
		if (gameState.uiState.exitText.getGlobalBounds().contains(gameState.MousePosition.x, gameState.MousePosition.y))
		{
			gameState.uiState.exitText.setFillColor(sf::Color::Red);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				ToggleGameMode(gameState, gameState.PauseState);
				SetGameMode(gameState, gameState.MenuState);
				RestartGame(gameState);
			}
		}
		else
		{
			gameState.uiState.exitText.setFillColor(sf::Color::White);
		}
	}

	//Переключение режима(XOR)
	void ToggleGameMode(GameState& gameState, const int mode)
	{
		//00000000 (gamemode)
		//00000001 (mode)
		//   =
		//00000001 - true
		gameState.GameMode ^= mode;
	}

	//Установка режима(Устанавливаем нужный бит)
	void SetGameMode(GameState& gameState, const int mode)
	{
		//00000000 (gamemode)
		//00010000 (mode)
		//   =
		//00010000 - true
		gameState.GameMode |= mode;
	}

	//Проверка мода(установлен ли бит)
	bool CheckGameMode(const GameState& gameState, const int mode)
	{
		return (gameState.GameMode & mode) != 0;
	}

	std::string GetModeText(const GameState& gameState, const int mode)
	{
		if (CheckGameMode(gameState, mode))
		{
			return "on";
		}
		return "off";
	}

	void DrawGame(GameState& gameState, sf::RenderWindow& window)
	{
			// Draw player
			DrawPlayer(gameState.player, window);
		
			// Draw apples
			for (Apple& apple : gameState.AppleVector)
			{
				DrawApple(apple, window);
			}
			// Draw rocks
			for (int i = 0; i < NUM_ROCKS; i++)
			{
				DrawRock(gameState.rocks[i], window);
			}

		// TODO:TESTMENU
		if (CheckGameMode(gameState, gameState.MenuState))
		{
			window.draw(gameState.menuSprite);
		}
		DrawUI(gameState.uiState, window);
	}
}
	


