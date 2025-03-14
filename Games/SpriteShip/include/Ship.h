#pragma once

#include "Actor/Actor.h"

#include "Component/AnimateSpriteComponent.h"
#include "SDL.h"

#define DefaultShipTypeName "BaseShip"

class Ship : public MultiExtend::Actor
{

public:
	Ship(
		MultiExtend::GameState * gmstate,
		MultiExtend::Renderer* renderer,
		const char* tag = DefaultShipTypeName,
		MultiExtend::Vector3 position = MultiExtend::Vector3(0.0f, 0.0f, 0.0f),
		MultiExtend::Vector3 scale = MultiExtend::Vector3(1.0f, 1.0f, 1.0f),
		MultiExtend::Vector3 rotation = MultiExtend::Vector3(0.0f, 0.0f, 0.0f),
		int updateorder = DEFAULT_UPDATEORDER_ACTOR);
	virtual ~Ship();

private:
	MultiExtend::AnimateSpriteComponent * m_animSC;

};