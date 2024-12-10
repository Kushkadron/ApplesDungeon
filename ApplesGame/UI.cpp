#include "UI.h"
#include <string>
#include "Game.h"

namespace ApplesGame
{
	void InitUI(UIState& uiState, const sf::Font& font)
	{

		InitText(uiState.scoreText, font, sf::Color::White, 35);

		InitText(uiState.inputHintText, font, sf::Color::White, 35, sf::Vector2f(1.f, 0.f), "Use arrow keys to move, Space to restart, ESC to exit");

		uiState.isGameOverTextVisible = false;
		uiState.gameOverText.setStyle(sf::Text::Bold);

		InitText(uiState.gameOverText, font, sf::Color::Red, 100, sf::Vector2f(0.5f, 0.5f), "GAME OVER");
		InitText(uiState.mainMenuText, font, sf::Color::White, 120, sf::Vector2f(0.5f, 0.5f), "MENU");
		InitText(uiState.accelerationModeText, font, sf::Color::White, 48, sf::Vector2f(0.5f, 0.5f), "Acceleration mode: ");
		InitText(uiState.endModeText, font, sf::Color::White, 48, sf::Vector2f(0.5f, 0.5f), "Endless mode: ");
		InitText(uiState.infinityModeText, font, sf::Color::White, 48, sf::Vector2f(0.5f, 0.5f), "Arcade mode: ");
		InitText(uiState.continueText, font, sf::Color::White, 60, sf::Vector2f(0.5f, 0.5f), "Continue");
		InitText(uiState.exitText, font, sf::Color::White, 60, sf::Vector2f(0.5f, 0.5f), "Exit game");

		uiState.continueText.setPosition(500.f, SCREEN_HEGHT / 2);
		uiState.exitText.setPosition(500.f, SCREEN_HEGHT / 2 + 100);

		uiState.blurTexture.create(SCREEN_WIDTH, SCREEN_HEGHT);
		uiState.blurTexture.clear(sf::Color(0, 0, 0, 200));
		uiState.blurSprite.setTexture(uiState.blurTexture.getTexture());

		for (int i = 0; i < SIZE_LEADERBOARD; ++i)
		{
			int Score;
			std::string Name = uiState.NameTableVec[i];
			if (Name != "You")
			{
				Score = Get_Random_Int(0, NUM_APPLES);
			}
			else
			{
				Score = 0;
			}
			uiState.ScoreTableMap.emplace(Score, Name);

		}
	}

	void InitText(sf::Text& text, const sf::Font& font, sf::Color color, int size, const sf::Vector2f& origin, const std::string& name)
	{
		text.setFont(font);
		text.setCharacterSize(size);
		text.setFillColor(sf::Color(color));
		text.setString(name);
		text.setOrigin(origin);
	}

	void InitLeaderBoard(UIState& uiState, GameState& gameState)
	{
		int i = 0;

		// Основной цикл по ScoreTableMap
		for (auto it = uiState.ScoreTableMap.begin(); it != uiState.ScoreTableMap.end();) 
		{
			if (it->second == "You") 
			{
				// Сохраняем имя игрока
				std::string playerName = it->second;

				// Удаляем старую запись и обновляем итератор
				it = uiState.ScoreTableMap.erase(it);

				// Добавляем игрока обратно с новыми очками
				uiState.ScoreTableMap.insert({ gameState.numEatenApples, playerName });
			}
			else 
			{
				// Если текущий элемент не требует обновления, просто переходим к следующему
				++it;
			}
		}

		// Обновляем текст для отображения
		for (const auto& pair : uiState.ScoreTableMap) 
		{
			InitText(uiState.LeaderBoardText[i], gameState.font, sf::Color::White, 50, sf::Vector2f(0.5f, 0.5f));
			uiState.LeaderBoardText[i].setString(pair.second + "  " + std::to_string(pair.first));
			++i;
		}
	}

	void UpdateUI(UIState& uiState, GameState& gameState, float timeDelta)
	{
		uiState.scoreText.setString("Apples eaten: " + std::to_string(gameState.numEatenApples));


		//Геймовер
		if (CheckGameMode(gameState, gameState.GameOverState))
		{
			uiState.isGameOverTextVisible = true;
			uiState.isScoreTableTextVisible = true;
			sf::Color gameOverTextColor = (int)gameState.timeSinceGameOver % 2 ? sf::Color::Yellow : sf::Color::White;
			uiState.gameOverText.setFillColor(gameOverTextColor);
		}
		else
		{
			uiState.isGameOverTextVisible = false;
			uiState.isScoreTableTextVisible = false;
		}

		//Меню
		if (CheckGameMode(gameState, gameState.MenuState))
		{
			uiState.isMenuTextVisible = true;
			uiState.accelerationModeText.setString("Acceleration mode: " + std::string(GetModeText(gameState, ACCELERATION_MODE)));
			uiState.endModeText.setString("Regular mode: " + std::string(GetModeText(gameState, END_MODE)));
			uiState.infinityModeText.setString("Arcade mode: " + std::string(GetModeText(gameState, INFINITE_MODE)));
		}
		else
		{
			uiState.isMenuTextVisible = false;
		}
		//Пауза
		if (CheckGameMode(gameState, gameState.PauseState))
		{
			uiState.isScoreTableTextVisible = true;
		}
		else if (CheckGameMode(gameState, gameState.PlayingState))
		{
			uiState.isScoreTableTextVisible = false;
		}
		
		InitLeaderBoard(uiState, gameState);
	}

	void DrawUI(UIState& uiState, sf::RenderWindow& window)
	{
		//Режимы
		if (uiState.isMenuTextVisible)
		{
			//Текст меню
			uiState.mainMenuText.setPosition(425.f, 250.f);
			window.draw(uiState.mainMenuText);
			//Ускорение
			uiState.accelerationModeText.setPosition(350.f, 450.f);
			window.draw(uiState.accelerationModeText);
			//Конечный режим
			uiState.endModeText.setPosition(350.f, 515.f);
			window.draw(uiState.endModeText);
			//Бесконечный режим
			uiState.infinityModeText.setPosition(350.f, 580.f);
			window.draw(uiState.infinityModeText);
		}
		else
		{
			uiState.scoreText.setPosition(25.f, 10.f);
			window.draw(uiState.scoreText);

			uiState.inputHintText.setPosition({ SCREEN_WIDTH / 3.5f, 10.f });
			window.draw(uiState.inputHintText);
		}

		//Геймовер
		if (uiState.isGameOverTextVisible)
		{
			float offsetPositionX = 250.f;
			uiState.gameOverText.setPosition(SCREEN_WIDTH / 2.f - offsetPositionX, SCREEN_HEGHT / 2.25f - 50.f);
			window.draw(uiState.gameOverText);
		}
		//Таблица рекордов
		if (uiState.isScoreTableTextVisible)
		{	
			window.draw(uiState.blurSprite);
			window.draw(uiState.continueText);
			window.draw(uiState.exitText);
			int OffsetY = 65;
			int VerticalPosition = 100;

			for (int i = 0; i < SIZE_LEADERBOARD; ++i)
			{
				uiState.LeaderBoardText[i].setPosition(500.f, VerticalPosition);
				window.draw(uiState.LeaderBoardText[i]);
				VerticalPosition += OffsetY;
			}
		}
	}

}

