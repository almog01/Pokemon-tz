#pragma once
#include <string>

// Movement directions
enum Direction
{
	Down, Up, Right, Left
};

class Settings
{
public:

	// Window
	static const float WINDOW_WIDTH() { return 800.f; }		// window width
	static const float WINDOW_HEIGHT() { return 800.f; }	// window height
	static const std::string WINDOW_TITLE() { return "Pokemon-tz"; }// game title

	// Graphics
	static const int FPS() { return 60; }			// frame per second
	static const float GAME_SPEED() { return 8.f; }	// game speed
	static const float BASE() { return 16.f; }
	//static const float SCALE() { return 2.f; }
};

