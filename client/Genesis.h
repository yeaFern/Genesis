#pragma once

#include <olcPixelGameEngine.h>

class Layer
{
private:
	olc::Renderable m_Sprite;
	olc::PixelGameEngine* m_Engine;

	int m_Scale;
public:
	Layer(olc::PixelGameEngine* engine, int scale)
		: m_Engine(engine), m_Scale(scale)
	{
		m_Sprite.Create(engine->ScreenWidth() / scale, engine->ScreenHeight() / scale);
	}

	void Bind()
	{
		m_Engine->SetDrawTarget(m_Sprite.Sprite());
	}

	void Blit()
	{
		m_Engine->SetDrawTarget(nullptr);
		m_Engine->DrawSprite(0, 0, m_Sprite.Sprite(), m_Scale);
		// m_Engine->DrawDecal({ 0, 0 }, m_Sprite.Decal(), { float(m_Scale), float(m_Scale) });
	}
};

class Genesis : public olc::PixelGameEngine
{
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float dt) override;
};
