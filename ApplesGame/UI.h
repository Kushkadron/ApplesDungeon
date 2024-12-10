#pragma once
#include "Math.h"

namespace ApplesGame
{
	struct LeaderBoard
	{
		std::string Name;
		int Score;
	};
	struct UIState
	{
		bool isGameOverTextVisible = false;
		bool isMenuTextVisible = false;
		bool isScoreTableTextVisible = false;
		//modes
		sf::Text mainMenuText;
		sf::Text accelerationModeText;
		sf::Text endModeText;
		sf::Text infinityModeText;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Text gameOverText;
		sf::Text continueText;
		sf::Text exitText;

		sf::Text LeaderBoardText[SIZE_LEADERBOARD];

		sf::RenderTexture blurTexture;
		sf::Sprite blurSprite;

		std::vector <std::string> NameTableVec
		{
			{"Olga"}, {"Victor"}, {"Tanya"}, {"Petya"}, {"You"}
		};
		std::multimap<int, std::string, std::greater<>> ScoreTableMap;
	};
	struct GameState;
	void InitUI(UIState& uiState, const sf::Font& font);
	void InitText(sf::Text& text, const sf::Font& font, sf::Color color, int size, const sf::Vector2f& origin = { 0.f, 0.f }, const std::string& name= "Default");
	void InitLeaderBoard(UIState& uiState, GameState& gameState);
	void UpdateUI(UIState& uiState, GameState& gameState, float timeDelta);
	void DrawUI(UIState& uiState, sf::RenderWindow& window);
}
