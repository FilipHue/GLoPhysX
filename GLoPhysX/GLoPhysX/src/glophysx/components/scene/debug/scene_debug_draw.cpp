#include "gxpch.h"
#include "scene_debug_draw.h"

SceneDebugDraw::SceneDebugDraw() : m_points(nullptr), m_lines(nullptr), m_triangles(nullptr) {}

SceneDebugDraw::~SceneDebugDraw() {
    Destroy();
}

void SceneDebugDraw::Init() {
    m_points = new GLRenderPoints;
    m_points->Create();
    m_lines = new GLRenderLines;
    m_lines->Create();
    m_triangles = new GLRenderTriangles();
    m_triangles->Create();
}

void SceneDebugDraw::Destroy() {
    if (m_points) {
        m_points->Destroy();
        delete m_points;
        m_points = nullptr;
    }
    if (m_lines) {
        m_lines->Destroy();
        delete m_lines;
        m_lines = nullptr;
    }
    if (m_triangles) {
        m_triangles->Destroy();
        delete m_triangles;
        m_triangles = nullptr;
    }
}

void SceneDebugDraw::Toggle() {
    m_active = !m_active;
}

void SceneDebugDraw::Flush() {
    if (!m_active) return;
    m_lines->Flush();
    m_points->Flush();
    m_triangles->Flush();
}

void SceneDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    if (!m_active) return;
    b2Vec2 p1 = vertices[vertexCount - 1];
    for (int32 i = 0; i < vertexCount; ++i) {
        b2Vec2 p2 = vertices[i];
        m_lines->Batch(p1, color);
        m_lines->Batch(p2, color);
        p1 = p2;
    }
}

void SceneDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);

    for (int i = 1; i < vertexCount - 1; ++i)
    {
        m_triangles->Batch(vertices[0], fillColor);
        m_triangles->Batch(vertices[i], fillColor);
        m_triangles->Batch(vertices[i + 1], fillColor);
    }

    b2Vec2 p1 = vertices[vertexCount - 1];
    for (int i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p2 = vertices[i];
        m_lines->Batch(p1, color);
        m_lines->Batch(p2, color);
        p1 = p2;
    }
}

void SceneDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    if (!m_active) return;

    const int segments = 16;
    const float increment = 2.0f * b2_pi / segments;
    float sinInc = sinf(increment);
    float cosInc = cosf(increment);
    b2Vec2 r1(1.0f, 0.0f);
    b2Vec2 v1 = center + radius * r1;

    for (int i = 0; i < segments; ++i) {
        b2Vec2 r2;
        r2.x = cosInc * r1.x - sinInc * r1.y;
        r2.y = sinInc * r1.x + cosInc * r1.y;
        b2Vec2 v2 = center + radius * r2;
        m_lines->Batch(v1, color);
        m_lines->Batch(v2, color);
        r1 = r2;
        v1 = v2;
    }
}

void SceneDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    const float k_segments = 16.0f;
    const float k_increment = 2.0f * b2_pi / k_segments;
    float sinInc = sinf(k_increment);
    float cosInc = cosf(k_increment);
    b2Vec2 v0 = center;
    b2Vec2 r1(cosInc, sinInc);
    b2Vec2 v1 = center + radius * r1;
    b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
    for (int32 i = 0; i < k_segments; ++i)
    {
        // Perform rotation to avoid additional trigonometry.
        b2Vec2 r2;
        r2.x = cosInc * r1.x - sinInc * r1.y;
        r2.y = sinInc * r1.x + cosInc * r1.y;
        b2Vec2 v2 = center + radius * r2;
        m_triangles->Batch(v0, fillColor);
        m_triangles->Batch(v1, fillColor);
        m_triangles->Batch(v2, fillColor);
        r1 = r2;
        v1 = v2;
    }

    r1.Set(1.0f, 0.0f);
    v1 = center + radius * r1;
    for (int32 i = 0; i < k_segments; ++i)
    {
        b2Vec2 r2;
        r2.x = cosInc * r1.x - sinInc * r1.y;
        r2.y = sinInc * r1.x + cosInc * r1.y;
        b2Vec2 v2 = center + radius * r2;
        m_lines->Batch(v1, color);
        m_lines->Batch(v2, color);
        r1 = r2;
        v1 = v2;
    }

    // Draw a line fixed in the circle to animate rotation.
    b2Vec2 p = center + radius * axis;
    m_lines->Batch(center, color);
    m_lines->Batch(p, color);
}

void SceneDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    if (!m_active) return;
    m_lines->Batch(p1, color);
    m_lines->Batch(p2, color);
}

void SceneDebugDraw::DrawTransform(const b2Transform& xf) {
    const float k_axisScale = 0.4f;
    b2Color red(1.0f, 0.0f, 0.0f);
    b2Color green(0.0f, 1.0f, 0.0f);
    b2Vec2 p1 = xf.p, p2;

    m_lines->Batch(p1, red);
    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    m_lines->Batch(p2, red);

    m_lines->Batch(p1, green);
    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    m_lines->Batch(p2, green);
}

void SceneDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
    if (!m_active) return;
    m_points->Batch(p, color, size);
}
