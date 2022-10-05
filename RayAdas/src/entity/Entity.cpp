#include "RApch.h"
#include "Entity.h"

namespace RayAdas {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}