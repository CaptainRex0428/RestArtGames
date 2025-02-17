#pragma once

#include "Component.h"
#include "Vector/Vector.h"

#include <iostream>
#include <variant>

#define BaseActorComponentTypeName "BaseActorComponent"

class ActorComponent : public Component
{
public:
	ActorComponent(SDL_Renderer* renderer, 
		const char* tag = BaseActorComponentTypeName, 
		Vector3 postion = Vector3(0.0f, 0.0f, 0.0f),
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f),
		int updateorder = DefaultUpdateOrder);
	virtual ~ActorComponent();

	virtual void Update(float delta) override;

	virtual void Draw() override;

	void UpdateComponents(float delta);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	const std::vector<Component*>& GetComponents();
	Component* GetComponent(const char* component_tag);

	void UpdateChildActorComponents(float delta);
	void AddChildActorComponent(ActorComponent* child);
	void RemoveChildActorComponent(ActorComponent* child);
	const std::vector<ActorComponent*>& GetChildActorComponents();
	ActorComponent* GetChildActorComponent(const char* component_tag);

	void AttachParentActorComponent(ActorComponent* parent);
	void DettachParentActorComponent();
	ActorComponent* GetParentActorComponent();

	const Vector3& GetPosition();
	const Vector3& GetScale();
	const Vector3& GetRotation();

	void SetPosition(Vector3 pos);
	void SetScale(Vector3 scale);
	void SetRotation(Vector3 rotation);

	const Vector3 GetPositionResult();
	const Vector3 GetScaleResult();
	const Vector3 GetRotationResult();

	bool operator==(ActorComponent* other);
	
protected:
	void ClearParentActorComponent();

	void SetParentActorComponent(ActorComponent* parent);

protected:
	
	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_rotation;

private:

	ActorComponent* m_parent_component;

	// need update & draw
	std::vector<Component*> m_components;
	std::vector<ActorComponent*> m_child_actor_components;
	
};