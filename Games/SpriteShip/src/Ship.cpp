#include "Ship.h"
#include "MultiExtend.h"

Ship::Ship(
	MultiExtend::GameState* gmstate,
	MultiExtend::Renderer* renderer,
	const char* tag, 
	MultiExtend::Vector3 position,
	MultiExtend::Vector3 scale,
	MultiExtend::Vector3 rotation,
	int updateorder)
	: 
	MultiExtend::Actor(tag,position,scale,rotation,updateorder),
	m_animSC(nullptr)
{
	m_animSC = new MultiExtend::AnimateSpriteComponent(30,gmstate, renderer, nullptr,"RocketComponent");

	std::vector<MultiExtend::Texture*> texts = {
		MultiExtend::LoadTexture(gmstate,renderer, "../Games/SpriteShip/assets/Ship01.png"),
		MultiExtend::LoadTexture(gmstate,renderer, "../Games/SpriteShip/assets/Ship02.png"),
		MultiExtend::LoadTexture(gmstate,renderer, "../Games/SpriteShip/assets/Ship03.png"),
		MultiExtend::LoadTexture(gmstate,renderer, "../Games/SpriteShip/assets/Ship04.png")
	};
		
	m_animSC->SetAnimTextures(texts);

	GetActorComponentRoot()->AddChildActorComponent(m_animSC);
}

Ship::~Ship()
{
}
