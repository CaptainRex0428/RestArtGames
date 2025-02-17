#pragma once 

#include "Component/ActorComponent.h"

#define BaseSpriteComponentTypeName "BaseSpriteComponent"

class SpriteComponent : public ActorComponent
{
public:
	SpriteComponent(
		SDL_Renderer* renderer,
		const char* texturefilepath = nullptr, 
		const char* tag = BaseSpriteComponentTypeName,
		Vector3 postion = Vector3(0.0f, 0.0f, 0.0f),
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f),
		int updateorder = DefaultUpdateOrder);
	virtual ~SpriteComponent();

	virtual void Update(float delta);
	virtual void Draw() override;
	virtual void SetSingleTexture(SDL_Texture* texture);

protected:
	SDL_Texture* m_canva_texture;
	int m_TextureRender_w;
	int m_TextureRender_h;
};