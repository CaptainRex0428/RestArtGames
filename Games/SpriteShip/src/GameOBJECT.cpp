#include "GameOBJECT.h"

#include "SDL_image.h"
#include <fstream>


void GameOBJECT::AddActor(Actor* actor)
{
	if (std::find(Get()->m_actors.begin(), Get()->m_actors.end(), actor) == Get()->m_actors.end())
	{
		int order = actor->GetUpdateOrder();
		auto iter = Get()->m_actors.begin();
		for (;iter != Get()->m_actors.end();++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}
        Get()->m_actors.insert(iter,actor);
	}
}

void GameOBJECT::RemoveActor(Actor* actor)
{
	auto it = std::remove_if(Get()->m_actors.begin(), Get()->m_actors.end(),
        [actor](Actor* ac) -> bool {return *actor->GetTag() == *ac->GetTag(); });
    Get()->m_actors.erase(it);
}

SDL_Texture* GameOBJECT::LoadTexture(SDL_Renderer* renderer, const char* filepath)
{
	
	std::ifstream f(filepath);

	if (!f.good())
	{
		SDL_Log("File Doesn't exist :%s", filepath);
		return nullptr;
	}

	SDL_Surface* surf = IMG_Load(filepath);

	if (!surf)
	{
		SDL_Log("Failed to load texture file :%s", filepath);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);

	if (texture == nullptr)
	{
		SDL_Log("Failed to convert surface to texture :%s", filepath);
		return nullptr;
	}

	Get()->m_textures.emplace_back(texture);

	return texture;
}

bool GameOBJECT::Update(float delta)
{
	for (auto actor : Get()->m_actors)
	{
		actor->Update(delta);
	}

	return true;
}

void GameOBJECT::Draw()
{
	for (auto actor : Get()->m_actors)
	{
		actor->Draw();
	}
}

GameOBJECT * GameOBJECT::Get()
{
    static GameOBJECT instance;
    return &instance;
}
