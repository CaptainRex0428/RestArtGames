#pragma once

#include "Actor/Actor.h"

#include "Component/AnimSpriteComponent.h"

#define DefaultShipTypeName "BaseShip"

class Ship : public Actor
{

public:
	Ship(SDL_Renderer* renderer,
		const char* tag = DefaultShipTypeName,
		Vector3 position = Vector3(0.0f, 0.0f, 0.0f),
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f),
		int updateorder = DefaultActorUpdateOrder);
	virtual ~Ship();

private:
	AnimSpriteComponent* m_animSC;

};