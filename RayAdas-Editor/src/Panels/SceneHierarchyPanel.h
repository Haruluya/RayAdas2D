#pragma once
#include "RayAdas.h"
#include "utils/Base.h"
#include "entity/Scene.h"
#include "entity/Entity.h"


namespace RayAdas {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const SRef<Scene>& scene);

		void SetContext(const SRef<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		template<typename T>
		void DisplayAddComponentEntry(const std::string& entryName);

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		SRef<Scene> m_Context;
		Entity m_SelectionContext;
	};

}