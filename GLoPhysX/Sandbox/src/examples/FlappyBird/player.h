#pragma once

#include "glophysx.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class Player
{
public:
	Player(float x_pos, float y_pos);

	void Init();

	void Draw();
	void DrawGameOver(DeltaTime dt);
	void Update(DeltaTime dt);

	float GetXPos() const { return m_x_pos; }
	float GetYPos() const { return m_y_pos; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	void Reset(float x_pos, float y_pos_flipped, int animation_frame);

private:
	Shared<Texture2D> m_textures[3];
	int m_width, m_height;

	float m_rotation;
	float m_vertical_velocity;
	float m_velocity;
	float m_gravity;

	float m_x_pos;
	float m_y_pos;

	int m_animation_frame;
	int m_idle_frame;
	int m_flap;
};
