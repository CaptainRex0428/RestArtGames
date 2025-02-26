#include "Ship.h"

#include "GameOBJECT.h"

Ship::Ship(SDL_Renderer* renderer, 
	const char* tag, 
	Vector3 position, 
	Vector3 scale, 
	Vector3 rotation, 
	int updateorder)
	: 
	Actor(renderer,tag,position,scale,rotation,updateorder),
	m_animSC(nullptr)
{
	m_animSC = new AnimSpriteComponent(m_renderer, nullptr,"RocketComponent");

	std::vector<SDL_Texture*> texts = {
		GameOBJECT::LoadTexture(m_renderer, "../Games/SpriteShip/assets/Ship01.png"),
		GameOBJECT::LoadTexture(m_renderer, "../Games/SpriteShip/assets/Ship02.png"),
		GameOBJECT::LoadTexture(m_renderer, "../Games/SpriteShip/assets/Ship03.png"),
		GameOBJECT::LoadTexture(m_renderer, "../Games/SpriteShip/assets/Ship04.png")
	};
		
	m_animSC->SetAnimTextures(texts);

	GetActorComponentRoot()->AddChildActorComponent(m_animSC);
}

Ship::~Ship()
{
}
