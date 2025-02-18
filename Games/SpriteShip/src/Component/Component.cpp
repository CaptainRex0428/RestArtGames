#include "Component/Component.h"

#include "SDL_image.h"

#include <cstring>

Component::Component(SDL_Renderer * renderer, const char* tag, int updateorder)
	:m_updateorder(updateorder),m_component_state(CP_Valid | CP_Display),m_renderer(renderer)
{
	SetTag(BaseComponentTypeName);

	size_t len = std::strlen(tag);
	m_component_tag = new char[len];
	memcpy(m_component_tag, tag, len);
}

Component::~Component()
{
	delete m_component_tag;
}

int Component::GetUpdateOrder() const
{
	return m_updateorder;
}

const char* Component::GetTag()
{
	return m_component_tag;
}

void Component::SetComponentState(int state)
{
	m_component_state = state;
}

const int& Component::GetComponentState()
{
	return m_component_state;
}

void Component::SetTag(const char * type)
{
	size_t len = std::strlen(type);
	m_component_type = new char[len];
	memcpy(m_component_type, type, len);
}

void Component::Update(float delta)
{
	// update self
}

void Component::Draw()
{
	return;
}
