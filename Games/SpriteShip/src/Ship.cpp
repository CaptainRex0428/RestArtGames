#include "Ship.h"


Ship::Ship(SDL_Renderer* renderer, 
	const char* tag, 
	MultiExtend::Vector3 position,
	MultiExtend::Vector3 scale,
	MultiExtend::Vector3 rotation,
	int updateorder)
	: 
	MultiExtend::Actor(tag,position,scale,rotation,updateorder),
	m_animSC(nullptr)
{
	m_animSC = new MultiExtend::AnimateSpriteComponent(m_renderer, nullptr,"RocketComponent");

	std::vector<MultiExtend::Texture*> texts = {
		MultiExtend::LoadTexture(m_renderer, "../Games/SpriteShip/assets/Ship01.png"),
		MultiExtend::LoadTexture(m_renderer, "../Games/SpriteShip/assets/Ship02.png"),
		MultiExtend::LoadTexture(m_renderer, "../Games/SpriteShip/assets/Ship03.png"),
		MultiExtend::LoadTexture(m_renderer, "../Games/SpriteShip/assets/Ship04.png")
	};
		
	m_animSC->SetAnimTextures(texts);

	GetActorComponentRoot()->AddChildActorComponent(m_animSC);
}

Ship::~Ship()
{
}
