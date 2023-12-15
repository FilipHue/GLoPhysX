#include "player.h"

Player::Player(float x_pos, float y_pos)
{
	m_x_pos = x_pos;
	m_y_pos = y_pos;

	Init();
}

void Player::Init()
{
	m_textures[0] = Texture2D::Create("src/examples/FlappyBird/assets/objects/yellowbird-downflap.png", 1);
	m_textures[1] = Texture2D::Create("src/examples/FlappyBird/assets/objects/yellowbird-midflap.png", 1);
	m_textures[2] = Texture2D::Create("src/examples/FlappyBird/assets/objects/yellowbird-upflap.png", 1);

	m_width = m_textures[0]->GetWidth();
	m_height = m_textures[0]->GetHeight();

	m_x_pos -= m_width;

	m_rotation = 0.f;
	m_vertical_velocity = 200.f;
	m_gravity = 9.8f;
	m_velocity = 0.f;

	m_animation_frame = 0;
	m_idle_frame = 10;
	m_flap = 0;
}

void Player::Draw()
{
	Renderer2D::DrawRotatedQuad({ m_x_pos, m_y_pos, 0.5f }, { m_width, m_height }, glm::radians(m_rotation), m_textures[m_animation_frame / 10]);
}

void Player::DrawGameOver(DeltaTime dt)
{
	if (m_y_pos > 112) {
		m_velocity -= m_gravity;
		m_y_pos += m_velocity * dt;
	}

	m_rotation = -27.5f;

	Draw();
}

void Player::Update(DeltaTime dt)
{
	m_velocity -= m_gravity;

	m_y_pos += m_velocity * dt;

	if (Input::IsKeyPressed(GLOP_KEY_SPACE) || Input::IsMouseButtonPressed(GLOP_MOUSE_BUTTON_1)) {
		m_velocity = m_vertical_velocity;
		m_animation_frame = 0;
		m_flap = 1;
	}

	if (m_flap == 1) {
		m_animation_frame += 1;
		
		if (m_animation_frame >= 29) {
			m_flap = 0;
		}

		m_rotation = 27.5f - 27.5f * (m_animation_frame / 10.f);
	}

	if (m_flap == 0) {
		m_animation_frame = m_idle_frame;
	}
}

void Player::Reset(float x_pos, float y_pos, int animation_frame)
{
	m_x_pos = x_pos;
	m_y_pos = y_pos;

	m_velocity = 0.f;
	
	m_animation_frame = animation_frame;
}
