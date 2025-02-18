#pragma once

#include <vector>

#include "SDL.h"

#define DefaultUpdateOrder 100

#define BaseComponentTypeName "BaseComponent"

enum ComponentState
{
	CP_Valid = 0b00000001,
	CP_Display = 0b00000010
};

class Component
{
public:
	Component(SDL_Renderer * renderer, 
		const char* tag = BaseComponentTypeName,
		int updateorder = DefaultUpdateOrder);
	virtual ~Component();

	virtual void Update(float delta);

	virtual void Draw();

	int GetUpdateOrder() const;
	const char* GetTag();
	const int& GetComponentState();

	void SetComponentState(int state);

protected:
	virtual void SetTag(const char * type);

protected:
	int m_updateorder;
	SDL_Renderer * m_renderer;

private:
	char* m_component_tag;
	char* m_component_type;
	int m_component_state;
};