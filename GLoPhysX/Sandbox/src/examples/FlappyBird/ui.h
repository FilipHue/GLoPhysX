#pragma once

#include "glophysx.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class UI
{
public:
	UI();

	void Init();

	void DrawStartGame(int width, int height);
	void DrawGameOver(int width, int height);
	void DrawScore(int width, int height, int score);

private:
	Shared<Texture2D> m_start_game_screen;
	Shared<Texture2D> m_game_over_screen;
	std::vector<Shared<Texture2D>> m_digits;
};

