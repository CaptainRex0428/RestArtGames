#pragma once

#include <vector>

#include "Component/Component.h"
#include "Actor/Actor.h"

// Singleton Class
class GameOBJECT
{
public:

	static void AddActor(MultiExtend::Actor * actor);
	static void RemoveActor(MultiExtend::Actor* actor);

	static SDL_Texture* LoadTexture(SDL_Renderer * renderer,const char* filepath);

	static bool Update(float delta);
	static void Draw();

	GameOBJECT(GameOBJECT&) = delete;



	GameOBJECT() = default;
	virtual ~GameOBJECT() = default;

	static GameOBJECT * Get();


	std::vector<SDL_Texture*> m_textures;
	std::vector<Actor*> m_actors;
};