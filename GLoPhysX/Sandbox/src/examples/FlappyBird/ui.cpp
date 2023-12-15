#include "ui.h"

UI::UI()
{
	Init();
}

void UI::Init()
{
	m_start_game_screen = Texture2D::Create("src/examples/FlappyBird/assets/ui/message.png", 1);
	m_game_over_screen = Texture2D::Create("src/examples/FlappyBird/assets/ui/gameover.png", 1);

	m_digits = {
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/0.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/1.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/2.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/3.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/4.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/5.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/6.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/7.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/8.png", 1),
		Texture2D::Create("src/examples/FlappyBird/assets/ui/numbers/9.png", 1),
	};
}

void UI::DrawStartGame(int width, int height)
{
	Renderer2D::DrawQuad(
		{ (width - m_start_game_screen->GetWidth()) / 2, height - m_start_game_screen->GetHeight() - 50.f, 0.4f },
		{ m_start_game_screen->GetWidth(), m_start_game_screen->GetHeight() },
		m_start_game_screen);
}

void UI::DrawGameOver(int width, int height)
{
	Renderer2D::DrawQuad(
		{ (width - m_game_over_screen->GetWidth()) / 2, height - m_game_over_screen->GetHeight() - 50.f, 0.4f },
		{ m_game_over_screen->GetWidth(), m_game_over_screen->GetHeight() },
		m_game_over_screen);
}

void UI::DrawScore(int width, int height, int score = 0)
{
	int offset = m_digits[0]->GetWidth();
	int index = 0;

	if (score / 10 <= 0) {
		index = 0;
	}
	else if (score / 100 <= 0) {
		index = 1;
	}
	else {
		index = 2;
	}

	do {
		int digit = score % 10;

		Renderer2D::DrawQuad(
			{ 10 + offset * index, height - m_digits[digit]->GetHeight() - 10, 0.4f },
			{ m_digits[digit]->GetWidth(), m_digits[digit]->GetHeight() },
			m_digits[digit]);

		index -= 1;

		score /= 10;
	} while (score);
}
