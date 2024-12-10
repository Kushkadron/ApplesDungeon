 #pragma once
#include "SFML/Audio.hpp"	
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "UI.h"
#include <vector>

namespace ApplesGame
{
	struct GameState
	{
		//bool isGameOver = false;
		const char MenuState = 0b00001000;
		const char PlayingState = 0b00010000;
		const char PauseState = 0b00100000;
		const char GameOverState = 0b01000000;
		char GameMode = 0b00000000;
		int numEatenApples = 0;
		float timeSinceGameOver = 0.f;
		Player player;
		//Apple apples[NUM_APPLES];
		std::vector<Apple> AppleVector;
		Rock rocks[NUM_ROCKS];
		UIState uiState;
		sf::Vector2i MousePosition;


		sf::Sound appleEatSound;
		sf::Sound deathSound;

		// Game resources
		sf::Font font;
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Texture menuTexture;
		sf::Sprite menuSprite;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer GameOverSoundBuffer;

	};

	void InitGame(GameState& gameState);
	void RestartGame(GameState& gameState);
	void HandleInputMove(GameState& gameState);
	void UpdateGame(GameState& gameState, float timeDelta);
	void HandleInputCheck(GameState& gameState, sf::RenderWindow& window, sf::Event& event);
	void ToggleGameMode(GameState& gameState, const int mode);
	void SetGameMode(GameState& gameState, const int mode);
	bool CheckGameMode(const GameState& gameState, const int mode);
	std::string GetModeText(const GameState& gameState, const int mode);
	void DrawGame(GameState& gameState, sf::RenderWindow& window);
}
