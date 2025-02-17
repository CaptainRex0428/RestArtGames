#include "Component/ActorComponent.h"

ActorComponent::ActorComponent(
	SDL_Renderer * renderer, 
	const char* tag, 
	Vector3 position, 
	Vector3 scale, 
	Vector3 rotation,
	int updateorder)
	:
	Component(renderer,tag, updateorder), 
	m_parent_component(nullptr),
	m_position(position),
	m_scale(scale),
	m_rotation(rotation)
{
	InitType(BaseActorComponentTypeName);
}

ActorComponent::~ActorComponent()
{
	for (auto actor_component : m_child_actor_components)
	{
		actor_component->ClearParentActorComponent();
	}

	m_parent_component->RemoveChildActorComponent(this);
	m_parent_component = nullptr;
}

void ActorComponent::UpdateComponents(float delta)
{
	for (auto component : m_components)
	{
		component->Update(delta);
	}
}

void ActorComponent::AddComponent(Component* component)
{
	if (std::find(m_components.begin(),m_components.end(),
		component)==m_components.end())
	{
		int order = component->GetUpdateOrder();
		auto iter = m_components.begin();
		for (; iter != m_components.end(); ++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}

		m_components.insert(iter,component);
	}
}

void ActorComponent::RemoveComponent(Component* component)
{
	auto it = std::remove_if(m_components.begin(), m_components.end(), 
		[component](Component* comp) -> bool {return *component->GetTag() == *comp->GetTag(); });
	m_components.erase(it);
}

const std::vector<Component*>& ActorComponent::GetComponents()
{
	return m_components;
}

Component* ActorComponent::GetComponent(const char* component_tag)
{
	for (auto component : m_components)
	{
		if (*component->GetTag() == *component_tag)
		{
			return component;
		}
	}

	return nullptr;
}

void ActorComponent::UpdateChildActorComponents(float delta)
{
	for (auto child: m_child_actor_components)
	{
		child->Update(delta);
	}
}

void ActorComponent::AddChildActorComponent(ActorComponent* child)
{
	if (std::find(m_child_actor_components.begin(),
		m_child_actor_components.end(),
		child) == m_child_actor_components.end())
	{
		int order = child->GetUpdateOrder();
		auto iter = m_child_actor_components.begin();

		for (; iter != m_child_actor_components.end(); ++iter)
		{
			break;
		}

		child->SetParentActorComponent(this);

		m_child_actor_components.insert(iter,child);
	}
}

void ActorComponent::SetParentActorComponent(ActorComponent* parent)
{
	m_parent_component = parent;
}

void ActorComponent::RemoveChildActorComponent(ActorComponent* child)
{
	auto it = std::remove_if(m_child_actor_components.begin(),
		m_child_actor_components.end(), 
		[child](ActorComponent* ch) -> bool { return *child->GetTag() == *ch->GetTag(); });
	m_child_actor_components.erase(it);
}

const std::vector<ActorComponent*>& ActorComponent::GetChildActorComponents()
{
	return m_child_actor_components;
}

ActorComponent* ActorComponent::GetChildActorComponent(const char* component_tag)
{
	for (auto child : m_child_actor_components)
	{
		if (*child->GetTag() == *component_tag)
		{
			return child;
		}
	}

	return nullptr;
}

void ActorComponent::AttachParentActorComponent(ActorComponent* parent)
{
	if (std::find(m_child_actor_components.begin(),
		m_child_actor_components.end(),
		parent) == m_child_actor_components.end())
	{
		if (m_parent_component != parent)
		{
			if (m_parent_component != nullptr)
			{
				m_parent_component->RemoveChildActorComponent(this);
			}

			parent->AddChildActorComponent(this);

			m_parent_component = parent;
		}

		return;
	}
#ifdef DEBUG
	std::cout << "Cannot attach parent actor component to child actor component." << std::endl;
#endif
}

void ActorComponent::DettachParentActorComponent()
{
	if (m_parent_component != nullptr)
	{
		m_parent_component->RemoveChildActorComponent(this);
		m_parent_component = nullptr;
	}
}

ActorComponent* ActorComponent::GetParentActorComponent()
{
	return m_parent_component;
}

const Vector3& ActorComponent::GetPosition()
{
	return m_position;
}

const Vector3& ActorComponent::GetScale()
{
	return m_scale;
}

const Vector3& ActorComponent::GetRotation()
{
	return m_rotation;
}

void ActorComponent::SetPosition(Vector3 pos)
{
	m_position = pos;
}

void ActorComponent::SetScale(Vector3 scale)
{
	m_scale = scale;
}

void ActorComponent::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
}

const Vector3 ActorComponent::GetPositionResult()
{


	float p_x = m_position.x;
	float p_y = m_position.y;
	float p_z = m_position.z;

	ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		p_x += parent->GetPosition().x;
		p_y += parent->GetPosition().y;
		p_z += parent->GetPosition().z;

		parent = parent->GetParentActorComponent();
	}

	return Vector3(p_x, p_y, p_z);

}

const Vector3 ActorComponent::GetScaleResult()
{
	float scalesize_x = m_scale.x;
	float scalesize_y = m_scale.y;
	float scalesize_z = m_scale.z;
	ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		scalesize_x *= parent->GetScale().x;
		scalesize_y *= parent->GetScale().y;
		scalesize_z *= parent->GetScale().z;

		parent = parent->GetParentActorComponent();
	}

	return Vector3(scalesize_x, scalesize_y, scalesize_z);

}

const Vector3 ActorComponent::GetRotationResult()
{
	float r_x = m_rotation.x;
	float r_y = m_rotation.y;
	float r_z = m_rotation.z;
	ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		r_x *= parent->GetRotation().x;
		r_y *= parent->GetRotation().y;
		r_z *= parent->GetRotation().z;

		parent = parent->GetParentActorComponent();
	}

	return Vector3(r_x, r_y, r_z);

}

bool ActorComponent::operator==(ActorComponent* other)
{
	return this->GetTag() == other->GetTag();;
}

void ActorComponent::ClearParentActorComponent()
{
	if (m_parent_component->GetParentActorComponent() != nullptr)
	{
		m_parent_component = m_parent_component->GetParentActorComponent();
		return;
	}

	m_parent_component = nullptr;
}

void ActorComponent::Update(float delta)
{
	// update self

	for (auto child: m_child_actor_components)
	{
		child->Update(delta);
	}

	for (auto component : m_components)
	{
		component->Update(delta);
	}
	
	return;
}

void ActorComponent::Draw()
{
	// draw self
	
	for (auto component : m_components)
	{
		component->Draw();
	}

	for (auto child : m_child_actor_components)
	{
		child->Draw();
	}
}