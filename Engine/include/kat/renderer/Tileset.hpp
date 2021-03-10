#pragma once

#include <string>
#include <glm/glm.hpp>
#include "kat/renderer/Texture.hpp"

namespace kat {

	class Tileset {
	private:
		kat::Texture* m_Texture;
		uint32_t m_TileSize, m_RowSize;

		float m_w_ratio, m_h_ratio;
	public:
		Tileset(std::string filename, uint32_t tilesize);

		glm::vec4 getTile(uint32_t id);

		void bindTex();
		void bindTex(uint32_t unit);

		
	};
}