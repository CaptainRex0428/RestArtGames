#pragma once

#include "SpriteComponent.h"

#define BaseAnimSpriteComponentTypeName "BaseAnimSpriteComponent"

class AnimSpriteComponent :public SpriteComponent
{
public:
	AnimSpriteComponent(
		SDL_Renderer* renderer, 
		const char * canva_path, 
		const char* tag = BaseAnimSpriteComponentTypeName, 
		Vector3 postion = Vector3(0.0f, 0.0f, 0.0f),
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f),
		int updateorder = DefaultUpdateOrder);
	virtual ~AnimSpriteComponent();

	virtual void Update(float delta) override;

	void SetAnimTextures(const std::vector<SDL_Texture*>& anim_textures);
	
	float GetAnimFPS() const;
	void SetAnimFPS(float fps);

private:
	std::vector<SDL_Texture*> m_anim_textures;

	float m_anim_fps;
	float m_current_frame;

};