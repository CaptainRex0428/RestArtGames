#pragma once

#include "Actor/Actor.h"

#include "Component/ScrollComponent.h"

class BackGround : MultiExtend::Actor
{
public:
	BackGround(SDL_Renderer* renderer);
	virtual ~BackGround();

private:
	MultiExtend::ScrollComponent * Space;
	MultiExtend::ScrollComponent * Stars;
};