#pragma once

#include "SpriteComponent.h"

#include <vector>

#define BaseBKGComponentTypeName "BackgroundComponent"

struct BKGTexture
{
	SDL_Texture* texture;
	Vector2 offset;
};

class BKGComponent : public SpriteComponent
{
public:
	BKGComponent(
		SDL_Renderer* renderer,
		Vector2 screensize,
		float scrollspeed,
		int updateorder = DefaultUpdateOrder,
		const char* tag = BaseSpriteComponentTypeName,
		const char* texturefilepath = nullptr,
		Vector3 postion = Vector3(0.0f, 0.0f, 0.0f),
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f)
		);
	virtual ~BKGComponent();

	virtual void Update(float delta) override;
	virtual void Draw() override;

	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	void SetScreenSize(const Vector2 size);

	void SetScrollSpeed(float speed);
	float GetScrollSpeed() const;

private:
	std::vector<BKGTexture> m_BGTextures;
	Vector2 m_ScreenSize;
	float m_ScrollSpeed;

	float m_ScrollWidth;
};