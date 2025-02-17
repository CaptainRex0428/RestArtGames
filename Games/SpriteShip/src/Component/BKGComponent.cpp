#include "Component/BKGComponent.h"

BKGComponent::BKGComponent(SDL_Renderer* renderer,
	Vector2 screensize,
	float scrollspeed,
	int updateorder,
	const char* tag,
	const char* texturefilepath,
	Vector3 postion,
	Vector3 scale,
	Vector3 rotation)
	:
	SpriteComponent(renderer, texturefilepath, tag, postion, scale, rotation, updateorder),
	m_ScrollSpeed(scrollspeed),
	m_ScreenSize(screensize),
	m_ScrollWidth(0)
{
}

BKGComponent::~BKGComponent()
{
}

void BKGComponent::Update(float delta)
{
	SpriteComponent::Update(delta);

	for (auto & bg: m_BGTextures)
	{
		bg.offset.x += m_ScrollSpeed * delta;

		int w, h = 0;
		SDL_QueryTexture(bg.texture, nullptr, nullptr, &w, &h);

		if (bg.offset.x < -w)
		{

			bg.offset.x += m_ScrollWidth;
		}
	}
}

void BKGComponent::Draw()
{
	for (auto& bg : m_BGTextures)
	{
		SDL_Rect rc;
		SDL_Rect t;

		int w, h = 0;

		SDL_QueryTexture(bg.texture, nullptr, nullptr, &w, &h);

		rc.w = (int)(w);
		rc.h = (int)(h);
		rc.x = (int)(bg.offset.x);
		rc.y = 0;

		t.w = (int)(m_ScreenSize.x);
		t.h = (int)(m_ScreenSize.y);
		t.x = (int)(bg.offset.x);
		t.y = 0;

		SDL_RenderCopy(m_renderer, bg.texture, nullptr, &rc);
	}

}

void BKGComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;

	float offsetcount = 0;

	for (auto tex : textures)
	{
		BKGTexture temp;

		temp.texture = tex;
		temp.offset.x = offsetcount;
		temp.offset.y = 0;

		m_BGTextures.emplace_back(temp);

		int w, h = 0;

		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);

		offsetcount += w;

		count++;
	}

	m_ScrollWidth = offsetcount;
}

void BKGComponent::SetScreenSize(const Vector2 size)
{
	m_ScreenSize = size;
}

void BKGComponent::SetScrollSpeed(float speed)
{
	m_ScrollSpeed = speed;
}

float BKGComponent::GetScrollSpeed() const
{
	return m_ScrollSpeed;
}



