#pragma once

#include "glophysx.h"
#include "player.h"
#include "pipe.h"
#include "ui.h"

using namespace GLOPHYSX;
using namespace RENDERING;
using namespace COMPONENTS;

class GameLayer : public Layer
{
public:
	GameLayer();
	
	void LoadAssets(const char* assets_folder);
	void CreateCamera();
	void Init();

	void RenderBackground() const;
	void MoveBackground(DeltaTime dt);

	void RenderPipes();
	void MovePipes(DeltaTime dt);

	void CheckCollision();
	void Reset();

	void CalculateScore();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(DeltaTime dt) override;
	void OnEvent(Event& e) override;
	void OnGUIRender() override;

private:
	// Textures
	Shared<Texture2D> m_background_1;
	Shared<Texture2D> m_background_2;
	Shared<Texture2D> m_ground_1;
	Shared<Texture2D> m_ground_2;

	// Player
	Player* m_bird;

	// Pipes
	std::vector<Pipe*> m_pipes;
	float m_pipe_gap;

	// Background
	float m_bg1_ox;
	float m_bg2_ox;
	int m_bg_height;
	int m_bg_width;

	float m_gr1_ox;
	float m_gr2_ox;
	int m_gr_width;
	int m_gr_height;

	float m_bg_scroll_speed;
	float m_gr_scroll_speed;

	// Camera
	OrthographicCamera* m_camera;
	int m_width;
	int m_height;

	// Game
	bool m_start_game = false;
	bool m_game_over = false;

	int m_score;

	// UI
	UI* m_ui;
};

