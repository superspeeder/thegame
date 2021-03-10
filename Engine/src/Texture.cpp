#include "kat/renderer/Texture.hpp"
#include "kat/Utils.hpp"

kat::Texture::Texture(std::string filename) {
	stbi_set_flip_vertically_on_load(true);
	glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);

	std::string fn = kat::resourceFilename(TEXTURES_DIR + filename);

	unsigned char* data = stbi_load(fn.c_str(), &m_Width, &m_Height, nullptr, 4);

	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(false);
}

uint32_t kat::Texture::getWidth() {
	return m_Width;
}

uint32_t kat::Texture::getHeight() {
	return m_Height;
}

uint32_t kat::Texture::getTextureName() {
	return m_Texture;
}

void kat::Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void kat::Texture::bind(uint32_t unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	bind();
}