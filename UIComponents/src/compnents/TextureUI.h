#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "ICComponent.h"
#include <glad/glad.h>
namespace ImguiCp {
	class TextureUI : public ICComponent{
	public:
		static bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height,int=0,int=0);

	};
}