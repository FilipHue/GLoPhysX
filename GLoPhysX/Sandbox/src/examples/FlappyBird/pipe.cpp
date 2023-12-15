#include "pipe.h"

Pipe::Pipe(float x_pos, float y_pos, float y_pos_flipped)
{
	m_x_pos = x_pos;
	m_y_pos = y_pos;
	m_y_pos_flipped = y_pos_flipped;

	Init();
}

void Pipe::Init()
{
	m_texture = Texture2D::Create("src/examples/FlappyBird/assets/objects/pipe-green.png", 1);
	m_texture_flipped = Texture2D::Create("src/examples/FlappyBird/assets/objects/pipe-green.png");

	m_width = m_texture->GetWidth();
	m_height = m_texture->GetHeight();

	m_reset = 0;
	m_marked = 0;
}

void Pipe::Draw() const
{
	Renderer2D::DrawQuad({ m_x_pos, m_y_pos,         0.1f }, { m_width, m_height }, m_texture);
	Renderer2D::DrawQuad({ m_x_pos, m_y_pos_flipped, 0.1f }, { m_width, m_height }, m_texture_flipped);
}

void Pipe::Update(DeltaTime dt)
{
	m_x_pos -= 180.f * dt;

	if (m_x_pos < -(float)m_width) {
		m_x_pos = 576 - (float)m_width;
		m_reset = 1;
	}
}
