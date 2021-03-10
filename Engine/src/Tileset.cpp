#include "kat/renderer/Tileset.hpp"


kat::Tileset::Tileset(std::string filename, uint32_t tilesize) {
	m_Texture = new kat::Texture(filename);
	m_TileSize = tilesize;

	m_w_ratio = (float)tilesize / m_Texture->getWidth();
	m_h_ratio = (float)tilesize / m_Texture->getHeight();
	m_RowSize = m_Texture->getWidth() / tilesize;
}

glm::vec4 kat::Tileset::getTile(uint32_t id) {
	uint32_t row = id / m_RowSize;
	uint32_t col = id % m_RowSize;

	float u1 = m_w_ratio * col;
	float u2 = m_w_ratio * (col + 1);

	float v1 = m_h_ratio * row;
	float v2 = m_h_ratio * (row + 1);

	return { u1, v1, u2, v2 };
}

void kat::Tileset::bindTex() {
	m_Texture->bind();
}

void kat::Tileset::bindTex(uint32_t unit) {
	m_Texture->bind(unit);
}

