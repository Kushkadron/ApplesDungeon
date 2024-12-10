#pragma once
#include <string>

namespace ApplesGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	constexpr float PLAYER_SIZE = 60.f;
	constexpr float APPLE_SIZE = 20.f;
	constexpr float ROCK_SIZE = 50;
	constexpr float INITIAL_SPEED = 150.f;
	constexpr float ACCELERATION = 20.f;
	constexpr int NUM_APPLES = 20;
	constexpr int NUM_ROCKS = 30;
	constexpr int SIZE_LEADERBOARD = 5;
	constexpr unsigned int SCREEN_WIDTH = 1200;
	constexpr unsigned int SCREEN_HEGHT = 1000;
	constexpr char INFINITE_MODE = 0b00000001;
	constexpr char END_MODE = 0b00000010;
	constexpr char ACCELERATION_MODE = 0b00000100;
}
