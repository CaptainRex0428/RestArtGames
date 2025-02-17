#include "Component/AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(
	SDL_Renderer* renderer,
	const char * canva_path, 
	const char* tag, 
	Vector3 postion,
	Vector3 scale,
	Vector3 rotation,
	int updateorder)
	:
	SpriteComponent(renderer,canva_path,tag,postion,scale,rotation,updateorder),
	m_anim_fps(30),
	m_current_frame(0)
{
	InitType(BaseAnimSpriteComponentTypeName);
}

AnimSpriteComponent::~AnimSpriteComponent()
{
}

void AnimSpriteComponent::Update(float delta)
{
	
	if (m_anim_textures.size() > 0)
	{
		m_current_frame += m_anim_fps * delta;
		
		// Wrap current frame if needed (set from begin)
		while (m_current_frame > m_anim_textures.size())
		{
			m_current_frame -= m_anim_textures.size();
		}

		SetSingleTexture(m_anim_textures[(int)m_current_frame]);
	}

	SpriteComponent::Update(delta);
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& anim_textures)
{
	m_anim_textures = anim_textures;
}

float AnimSpriteComponent::GetAnimFPS() const
{
	return m_anim_fps;
}

void AnimSpriteComponent::SetAnimFPS(float fps)
{
	m_anim_fps = fps;
}

