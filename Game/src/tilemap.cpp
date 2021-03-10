#include "tilemap.hpp"

#include <kat/renderer/Renderer.hpp>
#include <spdlog/spdlog.h>
#include <glm/gtc/matrix_transform.hpp>
#include <random>


bool isChunkInit = false;
kat::ElementBuffer* genericChunkEBO;

void initChunkSystem() {
	if (!isChunkInit) {
		genericChunkEBO = new kat::ElementBuffer(TILES_PER_CHUNK * 6);
		for (uint32_t i = 0; i < TILES_PER_CHUNK; i++) {
			genericChunkEBO->setVal(i * 6 + 0, 0 + i * 4);
			genericChunkEBO->setVal(i * 6 + 1, 1 + i * 4);
			genericChunkEBO->setVal(i * 6 + 2, 2 + i * 4);
			genericChunkEBO->setVal(i * 6 + 3, 0 + i * 4);
			genericChunkEBO->setVal(i * 6 + 4, 3 + i * 4);
			genericChunkEBO->setVal(i * 6 + 5, 1 + i * 4);
		}
		genericChunkEBO->update();
		isChunkInit = true;
	}
}

Chunk::Chunk(kat::Tileset* ts, glm::ivec2 cp) {
	initChunkSystem();
	m_VAO = new kat::VertexArray();
	m_VBO = new kat::VertexBuffer(TILES_PER_CHUNK * 4 * 7, kat::BufferMode::DynamicDraw);
	m_MapData = (int32_t*)malloc(TILES_PER_CHUNK * sizeof(int32_t));
	for (int i = 0; i < TILES_PER_CHUNK; i++) {
		m_MapData[i] = -1;
	}

	m_VAO->attachEBO(genericChunkEBO);
	m_VAO->vbo(m_VBO, { 3, 2, 2 });

	m_Tileset = ts;
	m_Pos = cp;
	glm::ivec2 ts_ = { cp.x * CHUNK_SIZE * TILE_SIZE , cp.y * CHUNK_SIZE * TILE_SIZE };
	m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(ts_, 1.0f));

	spdlog::debug("Loaded Chunk ({0}, {1})", cp.x, cp.y);
}

void Chunk::Chunk::setTile(uint32_t x, uint32_t y, int32_t id) {
	m_MapData[y * CHUNK_SIZE + x] = id;
	mapDirty = true;
}

void Chunk::Chunk::update() {
	if (mapDirty) {
		m_TilesToRender = 0;
//		std::vector<float> mesh(TILES_PER_CHUNK * 4 * 5);
		std::vector<float> mesh;
		for (int32_t y = 0; y < CHUNK_SIZE; y++) {
			for (int32_t x = 0; x < CHUNK_SIZE; x++) {
				int32_t id = getTile(x, y);
				int tx = x + m_Pos.x * CHUNK_SIZE;
				int ty = y + m_Pos.y * CHUNK_SIZE;
				glm::vec4 uvs = m_Tileset->getTile(id);

				if (id < 0) { uvs = { 0, 0, 0, 0 }; }


				mesh.push_back(x * TILE_SIZE);
				mesh.push_back(y * TILE_SIZE);
				mesh.push_back(0);
				mesh.push_back(uvs.x);
				mesh.push_back(uvs.y);
				mesh.push_back(tx);
				mesh.push_back(ty);

				mesh.push_back(x * TILE_SIZE + TILE_SIZE);
				mesh.push_back(y * TILE_SIZE + TILE_SIZE);
				mesh.push_back(0);
				mesh.push_back(uvs.z);
				mesh.push_back(uvs.w);
				mesh.push_back(tx);
				mesh.push_back(ty);

				mesh.push_back(x * TILE_SIZE);
				mesh.push_back(y * TILE_SIZE + TILE_SIZE);
				mesh.push_back(0);
				mesh.push_back(uvs.x);
				mesh.push_back(uvs.w);
				mesh.push_back(tx);
				mesh.push_back(ty);

				mesh.push_back(x * TILE_SIZE + TILE_SIZE);
				mesh.push_back(y * TILE_SIZE);
				mesh.push_back(0);
				mesh.push_back(uvs.z);
				mesh.push_back(uvs.y);
				mesh.push_back(tx);
				mesh.push_back(ty);

				m_TilesToRender++;
			}
		}

		m_VBO->update(mesh);
		mapDirty = false;
	}
}

void Chunk::draw(kat::ShaderProgram* shader) {
	if (mapDirty) {
		update();
	}

	m_Tileset->bindTex();
	shader->uniformMat4("uModel", m_Model);
	
	kat::drawElements(kat::DrawMode::Triangles, m_VAO, m_TilesToRender * 6);
}

int32_t Chunk::getTile(uint32_t x, uint32_t y) {
	return m_MapData[y * CHUNK_SIZE + x];
}

Chunk::~Chunk() {
	delete m_VBO;
	delete m_VAO;
}

ChunkManager::ChunkManager(kat::Tileset* ts) {
	m_Tileset = ts;
}

void ChunkManager::update(glm::vec2 pos) {
	glm::ivec2 centerc = { pos.x / TILE_SIZE / CHUNK_SIZE, pos.y / TILE_SIZE / CHUNK_SIZE };
	if (centerc != last_centerc) {

		std::vector<glm::ivec2> c2r;

		for (std::pair<const glm::ivec2, Chunk*> chunks : m_Chunks) {
			if (chunks.first.x < centerc.x - 2 || chunks.first.x > centerc.x + 2 || chunks.first.y < centerc.y - 2 || chunks.first.y > centerc.y + 2) {
				delete chunks.second;
				c2r.push_back(chunks.first);
			}
		}

		for (glm::ivec2 v : c2r) {
			m_Chunks.erase(v);
		}

		for (int x = centerc.x - 2; x < centerc.x + 3; x++) {
			for (int y = centerc.y - 2; y < centerc.y + 3; y++) {
				std::unordered_map<glm::ivec2, Chunk*>::iterator citr = m_Chunks.find({ x, y });
				if (citr == m_Chunks.end()) {
					m_Chunks.insert({ { x, y }, new Chunk(m_Tileset, { x, y }) });
				}
			}
		}
		last_centerc = centerc;
	}
}

void ChunkManager::draw(kat::ShaderProgram* shader, glm::vec2 pos) {
	update(pos);
	for (std::pair<const glm::ivec2, Chunk*> chunk : m_Chunks) {
		chunk.second->draw(shader);
	}
}

void ChunkManager::setTile(glm::vec2 tp, int32_t id) {
	glm::ivec2 cp = { (int)tp.x / (int)CHUNK_SIZE, (int)tp.y / (int)CHUNK_SIZE };
	glm::ivec2 itp = { (int)(tp.x) % CHUNK_SIZE, (int)(tp.y) % CHUNK_SIZE };

	if (tp.x < 0 && itp.x != 0) { 
		cp.x -= 1;
	}
	
	if (tp.y < 0 && itp.y != 0) {
		cp.y -= 1;
	}

	if (m_Chunks.find(cp) != m_Chunks.end()) {
		m_Chunks[cp]->setTile(itp.x, itp.y, id);
	}
}


