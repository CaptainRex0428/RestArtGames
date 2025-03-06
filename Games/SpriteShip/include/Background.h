#pragma once

#include "Actor/Actor.h"

#include "Component/ScrollComponent.h"

class BackGround : public MultiExtend::Actor
{
public:
	BackGround(MultiExtend::Renderer* renderer,MultiExtend::GameState * gmState);
	virtual ~BackGround();

private:
	MultiExtend::ScrollComponent * Space;
	MultiExtend::ScrollComponent * Stars;
};