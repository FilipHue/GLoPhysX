#include "game_layer.h"

GameLayer::GameLayer() : Layer("FlappyBird Game")
{
	m_width = 288;
	m_height = 512;
}

void GameLayer::LoadAssets(const char* assets_folder="examples/FlappyBird/assets")
{
	m_background_1 = Texture2D::Create("src/examples/FlappyBird/assets/objects/background-day.png", 1);
	m_background_2 = Texture2D::Create("src/examples/FlappyBird/assets/objects/background-day.png", 1);
	m_ground_1 = Texture2D::Create("src/examples/FlappyBird/assets/objects/base.png", 1);
	m_ground_2 = Texture2D::Create("src/examples/FlappyBird/assets/objects/base.png", 1);

	m_bg_width = m_background_1->GetWidth();
	m_bg_height = m_background_1->GetHeight();

	m_gr_width = m_ground_1->GetWidth();
	m_gr_height = m_ground_1->GetHeight();
}

void GameLayer::CreateCamera()
{
	m_camera = new OrthographicCamera(0.f, (float)m_width, 0.f, (float)m_height);
}

void GameLayer::Init()
{
	// Background
	m_bg1_ox = 0.f;
	m_bg2_ox = (float)m_bg_width;
	m_gr1_ox = 0.f;
	m_gr2_ox = (float)m_gr_width;

	m_bg_scroll_speed = 100.f;
	m_gr_scroll_speed = 180.f;

	// Player
	m_bird = new Player({ 100.f, m_bg_height / 2.f - 12.f });

	// Pipes
	m_pipe_gap = 100.f;

	float randy_1 = -100.f - rand() % 51;
	float randy_2 = -100.f - rand() % 51;
	float randy_3 = -100.f - rand() % 51;

	m_pipes = {
		new Pipe(m_width + 192.f,     randy_1, randy_1 + 336.f + m_pipe_gap),
		new Pipe(m_width + 192.f * 2, randy_2, randy_2 + 336.f + m_pipe_gap),
		new Pipe(m_width + 192.f * 3, randy_3, randy_3 + 336.f + m_pipe_gap)
	};

	// Score
	m_score = 0;

	// UI
	m_ui = new UI();
}

void GameLayer::RenderBackground() const
{
	Renderer2D::DrawQuad({ m_bg1_ox, 0.f       }, { m_bg_width + 10.f, m_bg_height }, m_background_1);
	Renderer2D::DrawQuad({ m_bg2_ox, 0.f       }, { m_bg_width + 10.f, m_bg_height }, m_background_2);
	Renderer2D::DrawQuad({ m_gr1_ox, 0.f, 0.3f }, { m_gr_width + 10.f, m_gr_height }, m_ground_1);
	Renderer2D::DrawQuad({ m_gr2_ox, 0.f, 0.3f }, { m_gr_width + 10.f, m_gr_height }, m_ground_2);
}

void GameLayer::MoveBackground(DeltaTime dt)
{
	if (m_start_game == false) {
		return;
	}

	m_bg1_ox -= dt * m_bg_scroll_speed;
	m_bg2_ox -= dt * m_bg_scroll_speed;
	m_gr1_ox -= dt * m_gr_scroll_speed;
	m_gr2_ox -= dt * m_gr_scroll_speed;

	if (m_bg1_ox < -(float)m_bg_width) {
		m_bg1_ox = (float)m_bg_width;
	}

	if (m_bg2_ox < -(float)m_bg_width) {
		m_bg2_ox = (float)m_bg_width;
	}

	if (m_gr1_ox < -(float)m_gr_width) {
		m_gr1_ox = (float)m_gr_width;
	}

	if (m_gr2_ox < -(float)m_gr_width) {
		m_gr2_ox = (float)m_gr_width;
	}
}

void GameLayer::RenderPipes()
{
	for (Pipe* pipe : m_pipes) {
		pipe->Draw();
	}
}

void GameLayer::MovePipes(DeltaTime dt)
{
	for (Pipe* pipe : m_pipes) {
		pipe->Update(dt);

		if (pipe->ShouldReset() == 1) {
			float y = -100.f - rand() % 51;
			pipe->SetY(y, y + pipe->GetHeight() + m_pipe_gap);
		}
	}
}

void GameLayer::CheckCollision()
{
	for (Pipe* pipe : m_pipes) {
		if (
			(m_bird->GetXPos() + m_bird->GetWidth() / static_cast<float>(2) > pipe->GetXPos() && m_bird->GetXPos() + m_bird->GetWidth() / 2 < pipe->GetXPos() + pipe->GetWidth()) &&
			(m_bird->GetYPos() < pipe->GetYPos() + pipe->GetHeight() || m_bird->GetYPos() + m_bird->GetHeight() / static_cast<float>(2) > pipe->GetYFlippedPos()))
		{
			m_start_game = false;
			m_game_over = true;
		}
	}
}

void GameLayer::Reset()
{
	m_bg1_ox = 0.f;
	m_bg2_ox = (float)m_bg_width;
	m_gr1_ox = 0.f;
	m_gr2_ox = (float)m_gr_width;

	m_bird->Reset(100.f, 2.f * m_height / 3, 10);

	float randy_1 = -100.f - rand() % 51;
	float randy_2 = -100.f - rand() % 51;
	float randy_3 = -100.f - rand() % 51;

	m_pipes[0]->SetX(m_width + 192.f);
	m_pipes[0]->SetY(randy_1, randy_1 + m_pipes[0]->GetHeight() + m_pipe_gap);

	m_pipes[1]->SetX(m_width + 192.f * 2);
	m_pipes[1]->SetY(randy_2, randy_2 + m_pipes[1]->GetHeight() + m_pipe_gap);

	m_pipes[2]->SetX(m_width + 192.f * 3);
	m_pipes[2]->SetY(randy_3, randy_3 + m_pipes[2]->GetHeight() + m_pipe_gap);

	m_score = 0;
}

void GameLayer::CalculateScore()
{
	for (Pipe* pipe : m_pipes) {
		if (m_bird->GetXPos() > pipe->GetXPos() && pipe->m_marked == 0) {
			m_score += 1;
			pipe->m_marked = 1;
		}
	}
}

void GameLayer::OnAttach()
{
	LoadAssets();
	CreateCamera();
	Init();
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(DeltaTime dt)
{
	if (m_game_over == false && (Input::IsKeyPressed(GLOP_KEY_SPACE) || Input::IsMouseButtonPressed(GLOP_MOUSE_BUTTON_1))) {
		m_start_game = true;
	}

	RendererCommands::SetClearColor();
	RendererCommands::Clear();

	Renderer2D::BeginScene(*m_camera);

	RenderBackground();
	MoveBackground(dt);

	if (m_game_over == false) {
		m_bird->Draw();
	}

	if (m_start_game == false && m_game_over == false) {
		m_ui->DrawStartGame(m_width, m_height);
	}

	if (m_start_game) {
		m_bird->Update(dt);

		RenderPipes();
		MovePipes(dt);

		CheckCollision();

		CalculateScore();

		m_ui->DrawScore(m_width, m_height, m_score);
	}

	if (m_game_over) {
		m_ui->DrawGameOver(m_width, m_height);
		m_ui->DrawScore(m_width, m_height, m_score);

		m_bird->DrawGameOver(dt);
		RenderPipes();

		if (Input::IsKeyPressed(GLOP_KEY_ENTER)) {
			m_game_over = false;
			m_start_game = true;
			Reset();
		}
	}

	Renderer2D::EndScene();
}

void GameLayer::OnEvent(Event& e)
{
}

void GameLayer::OnGUIRender()
{
}
