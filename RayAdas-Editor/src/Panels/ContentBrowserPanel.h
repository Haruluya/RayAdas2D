#pragma once
#include "RayAdas.h"
#include "rendering/Texture.h"

#include <filesystem>

namespace RayAdas {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;

		SRef<Texture2D> m_DirectoryIcon;
		SRef<Texture2D> m_FileIcon;
	};

}