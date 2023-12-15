#pragma once

#include "glophysx.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class Pipe
{
public:
	Pipe(float x_pos, float y_pos, float y_pos_flipped);

	void Init();
	void Draw() const;
	void Update(DeltaTime dt);

	void SetX(float x_pos) { m_x_pos = x_pos; }
	void SetY(float y_pos, float y_flipped) { m_y_pos = y_pos, m_y_pos_flipped = m_y_pos_flipped; m_reset = 0; m_marked = 0; }

	float GetXPos() const { return m_x_pos; }
	float GetYPos() const { return m_y_pos; }
	float GetYFlippedPos() const { return m_y_pos_flipped; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	bool ShouldReset() const { return m_reset; }

public:
	// For keeping the score
	int m_marked;

private:
	// Textures
	Shared<Texture2D> m_texture;
	Shared<Texture2D> m_texture_flipped;
	int m_width, m_height;

	// Position
	float m_x_pos, m_y_pos, m_y_pos_flipped;

	// For reseting the position after getting out of the rendering area
	int m_reset;
};

