#pragma once

#include "Actor/Actor.h"

#include "Component/BKGComponent.h"

class BackGround : Actor
{
public:
	BackGround(SDL_Renderer* renderer);
	virtual ~BackGround();

private:
	BKGComponent* Space;
	BKGComponent* Stars;
};