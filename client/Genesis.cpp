#include "Genesis.h"

#include "math/vec2.h"

#include <random>

static float m_Scale = 1;

static float camX = 0;
static float camY = 0;

static constexpr auto Pixel = (1.0f / 14.0f);

static const int m_Width = 16;
static const int m_Height = 16;
static bool m_Map[m_Width * m_Height];

class TextureMap
{
private:
	olc::Renderable m_Sprite;
public:
	TextureMap(const std::string& file)
	{
		m_Sprite.Load(file);
	}

	auto GetDecal() const
	{
		return m_Sprite.Decal();
	}

	std::tuple<olc::vf2d, olc::vf2d> Get(int x, int y, int w, int h)
	{
		float xs = float(x) / float(m_Sprite.Sprite()->width);
		float ys = float(y) / float(m_Sprite.Sprite()->height);
		float ws = float(w) / float(m_Sprite.Sprite()->width);
		float hs = float(h) / float(m_Sprite.Sprite()->height);

		return {
			{ xs, ys },
			{ xs + hs, ys + hs }
		};
	}
};

static TextureMap* m_Atlas;

class WorldRenderer
{
public:
	vec2 ToScreen(const vec2& world)
	{
		return
		{
			((world.x - camX) * 14.0f * m_Scale) + (640 / 2),
			((world.y - camY) * 14.0f * m_Scale) + (360 / 2)
		};
	}

	vec2 ToWorld(const vec2& screen)
	{
		return
		{
			camX + ((screen.x - (640 / 2)) / (14.0f * m_Scale)),
			camY + ((screen.y - (360 / 2)) / (14.0f * m_Scale))
		};
	}

	void Draw(float x, float y, olc::PixelGameEngine* e, int i)
	{
		auto s = ToScreen({ x, y });
		// e->DrawPartialDecal({ s.x, s.y }, { 14.0f * m_Scale, 14.0f * m_Scale }, m_Atlas.Decal(), { 14.0f * float(i), 0 }, { 14, 14 });

		// e->DrawPartialSprite(s.x, s.y, m_Atlas.Sprite(), 14 * i, 0, 14, 14, m_Scale);

		e->DrawPartialDecal({ s.x, s.y }, m_Atlas->GetDecal(), { float(14 * i), 0 }, { 14, 14 }, { m_Scale, m_Scale });
	}

	void DrawLine(float x1, float y1, float x2, float y2, olc::PixelGameEngine* e)
	{
		auto p1 = ToScreen({ x1, y1 });
		auto p2 = ToScreen({ x2, y2 });
		e->DrawLine(p1.x, p1.y, p2.x, p2.y, olc::RED);
	}

	void Wall(float x, float y, olc::PixelGameEngine* e)
	{
		auto s = ToScreen({ x, y - 0.5f });
		e->DrawPartialDecal({ s.x, s.y }, m_Atlas->GetDecal(), { 57, 0 }, { 14, 21 }, { m_Scale, m_Scale });
	}

	void WallDetailLeft(float x, float y, olc::PixelGameEngine* e)
	{
		{
			// Left
			auto s = ToScreen({ x - Pixel, y - 0.5f });
			e->DrawPartialDecal({ s.x, s.y }, m_Atlas->GetDecal(), { 72, 4 }, { 3, 14 }, { m_Scale, m_Scale });
		}
	}

	void WallDetailRight(float x, float y, olc::PixelGameEngine* e)
	{
		{
			// Right
			auto s = ToScreen({ x + (Pixel * 12), y - 0.5f });
			e->DrawPartialDecal({ s.x, s.y }, m_Atlas->GetDecal(), { 89, 4 }, { 3, 14 }, { m_Scale, m_Scale });
		}
	}

	void WallDetailTop(float x, float y, olc::PixelGameEngine* e)
	{
		{
			// Top
			auto s = ToScreen({ x, y - 0.5f - Pixel });
			e->DrawPartialDecal({ s.x, s.y }, m_Atlas->GetDecal(), { 75, 1 }, { 14, 3 }, { m_Scale, m_Scale });
		}
	}

	void WallDetailBottom(float x, float y, olc::PixelGameEngine* e)
	{
		{
			// Bottom
			auto s = ToScreen({ x, y + 0.5f - (Pixel * 2) });
			e->DrawPartialDecal({ s.x, s.y }, m_Atlas->GetDecal(), { 75, 18 }, { 14, 3 }, { m_Scale, m_Scale });
		}
	}

	void WallShadow(float x, float y, olc::PixelGameEngine* e)
	{
		auto s = ToScreen({ x, y + 1.0f });
		e->DrawPartialDecal({ s.x, s.y }, m_Atlas->GetDecal(), { 75, 22 }, { 14, 7 }, { m_Scale, m_Scale });
	}
};

template <typename T>
int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

static WorldRenderer m_WorldRenderer;

bool Genesis::OnUserCreate()
{
	m_Atlas = new TextureMap("assets/grass.png");

	return true;
}

bool Genesis::OnUserUpdate(float dt)
{
	m_Scale += sgn(this->GetMouseWheel());
	if (m_Scale < 1) { m_Scale = 1; }
	if (m_Scale > 3) { m_Scale = 3; }

	if (GetKey(olc::W).bHeld) { camY -= dt * 3.0f; }
	if (GetKey(olc::S).bHeld) { camY += dt * 3.0f; }
	if (GetKey(olc::A).bHeld) { camX -= dt * 3.0f; }
	if (GetKey(olc::D).bHeld) { camX += dt * 3.0f; }

	if (GetMouse(0).bHeld)
	{

		auto p = m_WorldRenderer.ToWorld({
			(float)GetMouseX(),
			(float)GetMouseY()
		});
		m_Map[int(p.x) + int(p.y) * m_Width] = true;
	}

	Clear(olc::WHITE);
	//m_WorldRenderer.Draw(0, 0, this);
	//m_WorldRenderer.Draw(1, 0, this);

	auto p = m_WorldRenderer.ToWorld({
		(float)GetMouseX(),
		(float)GetMouseY()
	});
	m_WorldRenderer.DrawLine(0, 0, p.x, p.y, this);

	// DrawSprite(0, 0, m_Atlas.Sprite(), 2);

	// DrawPartialSprite(0, 28, m_Atlas.Sprite(), 0, 0, 14, 14, 2);

	// m_WorldRenderer.Draw(0, 0, this, 0);
	// m_WorldRenderer.Draw(1.5f, 0, this, 1);

	srand(78123);

	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			m_WorldRenderer.Draw(x, y, this, rand() % 4);
		}
	}

	auto InRange = [&](int x, int y) { return x >= 0 && y >= 0 && x < m_Width && y < m_Height; };

	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			bool tile = m_Map[x + y * m_Width];

			bool l = InRange(x - 1, y) && m_Map[(x - 1) + y * m_Width];
			bool r = InRange(x + 1, y) && m_Map[(x + 1) + y * m_Width];
			bool t = InRange(x, y - 1) && m_Map[x + (y - 1) * m_Width];
			bool b = InRange(x, y + 1) && m_Map[x + (y + 1) * m_Width];

			if (tile)
			{
				m_WorldRenderer.Wall(x, y, this);

				if (!l) {
					m_WorldRenderer.WallDetailLeft(x, y, this);
				}

				if (!r) {
					m_WorldRenderer.WallDetailRight(x, y, this);
				}

				if (!t) {
					m_WorldRenderer.WallDetailTop(x, y, this);
				}

				if (!b) {
					m_WorldRenderer.WallDetailBottom(x, y, this);
					m_WorldRenderer.WallShadow(x, y, this);
				}
			}
		}
	}

	return true;
}
