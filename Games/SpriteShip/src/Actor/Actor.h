#pragma once

#include <vector>

#include "Component/ActorComponent.h"
#include "Vector/Vector.h"

#define DefaultActorTypeName "BaseActor"
#define DefaultActorUpdateOrder 100

enum ActorState
{
	ATR_Alive = 0b00000001,
	ATR_EPaused = 0b00000010
};

class Actor 
{
public:
	Actor(SDL_Renderer * renderer, 
		const char* tag = DefaultActorTypeName,
		Vector3 position = Vector3(0.0f, 0.0f, 0.0f),
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f),
		int updateorder = DefaultActorUpdateOrder);
	virtual ~Actor();

	virtual void Update(float delta);

	virtual void Draw();

	void UpdateComponents(float delta);
	void AddComponent(Component * component);
	void RemoveComponent(Component* component);
	const std::vector<Component*>& GetComponents();
	Component* GetComponent(const char* component_tag);

	void AddActorComponent(ActorComponent* actor_component);
	void RemoveActorComponent(ActorComponent* actor_component);
	ActorComponent* GetActorComponent(const char* actor_component_tag);

	ActorComponent* GetActorComponentRoot();
	void SetActorComponentRoot(ActorComponent * actor_component);

	void UpdateChildActors(float delta);
	void AddChildActor(Actor* child);
	void RemoveChildActor(Actor* child);
	const std::vector<Actor*>& GetChildActors();
	Actor* GetChildActor(const char* actor_tag);

	void AttachParentActor(Actor* parent);
	void DettachParentActor();
	Actor* GetParentActor();

	const char* GetTag();
	const int& GetUpdateOrder();

	const Vector3& GetPosition();
	const Vector3& GetRotation();
	const Vector3& GetScale();

	void SetPosition(Vector3 pos);
	void SetScale(Vector3 scale);
	void SetRotation(Vector3 rotation);

	const Vector3 GetPositionResult();
	const Vector3 GetScaleResult();
	const Vector3 GetRotationResult();

protected:
	virtual void InitType(const char* tag);
	void ClearParentActor();

protected:
	int m_state;

	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;

	SDL_Renderer* m_renderer;


private:
	int m_updateoreder;

	char* m_actor_tag;

	char* m_actor_type;

	Actor* m_parent_actor;

	// need update and draw

	ActorComponent* m_actor_component_root;

	std::vector<Component*> m_components;

	std::vector<Actor*> m_child_actors;
	
};

