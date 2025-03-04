

#include "GameOBJECT.h"

#include "SDL.h"

SpriteComponent::SpriteComponent(
	SDL_Renderer* renderer,
	const char* texturefilepath,
	const char* tag,
	Vector3 postion,
	Vector3 scale,
	Vector3 rotation,
	int updateorder)
	:
	MultiExtend::ActorComponent(tag,postion,scale,rotation,updateorder),
	m_canva_texture(nullptr),
	m_TextureRender_h(0),
	m_TextureRender_w(0)
{
	if (texturefilepath != nullptr)
	{
		SDL_Texture* texture = GameOBJECT::LoadTexture(m_renderer, texturefilepath);
		if (texture != nullptr)
		{
			m_canva_texture = texture;
		}
	}

	SetTag(BaseSpriteComponentTypeName);
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Update(float delta)
{
	ActorComponent::Update(delta);
}

void SpriteComponent::Draw()
{
	if (m_canva_texture)
	{
		SDL_Rect r;

		const Vector3 scaleresult = GetScaleResult();
		const Vector3 posresult = GetPositionResult();

		r.w = (int)(m_TextureRender_w * scaleresult.x);
		r.h = (int)(m_TextureRender_h * scaleresult.y);
		r.x = (int)(posresult.x - r.w / 2);
		r.y = (int)(posresult.y - r.h / 2);

		SDL_RenderCopyEx(m_renderer,
			m_canva_texture,
			nullptr,
			&r,
			GetRotationResult().z,
			nullptr,
			SDL_FLIP_NONE);
	}

	ActorComponent::Draw();
}

void MultiExtend::SpriteComponent::SetSingleTexture(SDL_Texture* texture)
{
	m_canva_texture = texture;

	SDL_QueryTexture(m_canva_texture, nullptr, nullptr, &m_TextureRender_w, &m_TextureRender_h);
}
