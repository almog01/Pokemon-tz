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
	static const float WINDOW_WIDTH() { return 800; }		// window width
	static const float WINDOW_HEIGHT() { return 800; }		// window height
	static const std::string WINDOW_TITLE() { return "Pokemon-tz"; }// game title

	// Graphics
	static const int FPS() { return 60; }			// frame per second
	static const float GAME_SPEED() { return 8; }	// game speed
	static const int BASE() { return 16; }
	static const int SCALE() { return 2; }
};

