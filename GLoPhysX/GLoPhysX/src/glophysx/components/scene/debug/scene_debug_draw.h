#pragma once

#include "utils.h"

#include "box2d/b2_draw.h"

class SceneDebugDraw : public b2Draw
{
public:
	SceneDebugDraw();
	~SceneDebugDraw();

	void Init();
	void Destroy();
	
	void SetProjectionMatrix(glm::mat4 projection_matrix) { 
		m_projection_matrix = projection_matrix; 
		m_points->SetProjection(m_projection_matrix);
		m_lines->SetProjection(m_projection_matrix);
	}

	void Toggle();

	void Flush();

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	void DrawTransform(const b2Transform& xf) override;

	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

public:
	GLRenderPoints* m_points;
	GLRenderLines* m_lines;
	GLRenderTriangles* m_triangles;

	glm::mat4 m_projection_matrix;

	bool m_active = true;
};

extern SceneDebugDraw m_scene_db_draw;
