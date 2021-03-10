#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string>
#include <cinttypes>

#define TEXTURES_DIR "Resources/Textures/"

namespace kat {

	class Texture {
	private:
		uint32_t m_Texture;
		int32_t m_Width, m_Height;

	public:

		Texture(std::string filename);

		uint32_t getWidth();
		uint32_t getHeight();

		uint32_t getTextureName();

		void bind();
		void bind(uint32_t unit);
	};
}