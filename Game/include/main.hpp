#pragma once

#include <kat/Application.hpp>
#include <kat/renderer/Buffer.hpp>
#include <kat/renderer/VertexArray.hpp>
#include <kat/renderer/Shader.hpp>

#include "tilemap.hpp"
#include "camera.hpp"

class GameApp : public kat::Application {
private:
	kat::VertexBuffer* vbo;
	kat::VertexArray* vao;
	kat::ElementBuffer* ebo;
	kat::ShaderProgram* shader, *shader2;
	ChunkManager* chunkManager;
	kat::Tileset* tileset;
	Camera* camera;
	kat::EventLayer* mainEventLayer;
	

protected:
	void render() override;
	void create() override;
	void destroy() override;
public:
	GameApp();
};