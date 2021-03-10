#pragma once

#include <unordered_map>

#include <kat/renderer/Buffer.hpp>
#include <kat/renderer/VertexArray.hpp>
#include <kat/renderer/Tileset.hpp>
#include <kat/renderer/Shader.hpp>

#include <glm/gtx/hash.hpp>

constexpr uint32_t CHUNK_SIZE = 32;
constexpr uint32_t TILES_PER_CHUNK = CHUNK_SIZE * CHUNK_SIZE;
constexpr uint32_t TILE_SIZE = 16;

extern kat::ElementBuffer* genericChunkEBO;
extern bool isChunkInit;

void initChunkSystem();

class Chunk {
private:
	int32_t* m_MapData;

	kat::VertexArray* m_VAO;
	kat::VertexBuffer* m_VBO;
	kat::Tileset* m_Tileset;

	bool mapDirty = true;
	uint32_t m_TilesToRender = 0;

	glm::ivec2 m_Pos;
	glm::mat4 m_Model;

public:

	Chunk(kat::Tileset* ts, glm::ivec2 cp);
	~Chunk();

	void setTile(uint32_t x, uint32_t y, int32_t id);
	int32_t getTile(uint32_t x, uint32_t y);

	void draw(kat::ShaderProgram* shader);
	void update();


};

class ChunkManager {
private:
	std::unordered_map<glm::ivec2, Chunk*> m_Chunks{};

	kat::Tileset* m_Tileset;
	glm::ivec2 last_centerc = { 100, 100 };

public:

	ChunkManager(kat::Tileset* ts);

	void update(glm::vec2 pos);

	void draw(kat::ShaderProgram* shader, glm::vec2 pos);

	void setTile(glm::vec2 tp, int32_t id);
};

