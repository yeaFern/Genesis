#include "Genesis.h"

#include "math/vec2.h"

#include <random>

static olc::Renderable m_Atlas;

static float m_Scale = 1;

static float camX = 0;
static float camY = 0;

class WorldRenderer
{
public:
	vec2 ToScreen(const vec2& world)
	{
		return
		{
			(float)((int)((world.x - camX) * 14.0f * m_Scale)),
			(float)((int)((world.y - camY) * 14.0f * m_Scale))
		};
	}

	vec2 ToWorld(const vec2& screen)
	{
		return
		{
			camX + (screen.x / (14.0f * m_Scale)),
			camY + (screen.y / (14.0f * m_Scale))
		};
	}

	void Draw(float x, float y, olc::PixelGameEngine* e, int i)
	{
		auto s = ToScreen({ x, y });
		// e->DrawPartialDecal({ s.x, s.y }, { 14.0f * m_Scale, 14.0f * m_Scale }, m_Atlas.Decal(), { 14.0f * float(i), 0 }, { 14, 14 });

		// e->DrawPartialSprite(s.x, s.y, m_Atlas.Sprite(), 14 * i, 0, 14, 14, m_Scale);

		e->DrawPartialDecal({ s.x, s.y }, m_Atlas.Decal(), { float(14 * i), 0 }, { 14, 14 }, { m_Scale, m_Scale });
	}

	void DrawLine(float x1, float y1, float x2, float y2, olc::PixelGameEngine* e)
	{
		auto p1 = ToScreen({ x1, y1 });
		auto p2 = ToScreen({ x2, y2 });
		e->DrawLine(p1.x, p1.y, p2.x, p2.y, olc::RED);
	}
};

static WorldRenderer m_WorldRenderer;

bool Genesis::OnUserCreate()
{
	m_Atlas.Load("assets/grass.png");

	return true;
}

bool Genesis::OnUserUpdate(float dt)
{
	// FillRect(80, 80, 7, 12, olc::RED);


	// Maybe between 2 and 3 scale (allow zoom)
	// (80, 100, 7 * 3, 12 * 3, olc::RED);

	if (GetKey(olc::E).bPressed) { m_Scale = 3; }
	if (GetKey(olc::Q).bPressed) { m_Scale = 2; }


	if (GetKey(olc::W).bHeld) { camY -= dt * 3.0f; }
	if (GetKey(olc::S).bHeld) { camY += dt * 3.0f; }
	if (GetKey(olc::A).bHeld) { camX -= dt * 3.0f; }
	if (GetKey(olc::D).bHeld) { camX += dt * 3.0f; }


	Clear(olc::WHITE);
	//m_WorldRenderer.Draw(0, 0, this);
	//m_WorldRenderer.Draw(1, 0, this);

	// auto p = m_WorldRenderer.ToWorld({
	// 	(float)GetMouseX(),
	// 	(float)GetMouseY()
	// });
	// m_WorldRenderer.DrawLine(0, 0, p.x, p.y, this);

	// DrawSprite(0, 0, m_Atlas.Sprite(), 2);

	DrawPartialSprite(0, 28, m_Atlas.Sprite(), 0, 0, 14, 14, 2);

	// m_WorldRenderer.Draw(0, 0, this, 0);
	// m_WorldRenderer.Draw(1.5f, 0, this, 1);

	srand(78123);
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 24; x++)
		{
			m_WorldRenderer.Draw(x, y, this, rand() % 4);
		}
	}

	return true;
}
