#include <iostream>

#include "main.hpp"

GameApp::GameApp() : kat::Application() {
	kat::ApplicationSettings settings{};
	settings.app_name = "Game";
	settings.app_version = GAME_VERSION;
	settings.windowSettings.title = settings.app_name + " " + settings.app_version;
	settings.windowSettings.width = 800;
	settings.windowSettings.height = 800;

	setSettings(settings);
}

Chunk* c, *c1;
int curT = 0;


void onKeyPressed(kat::KeyPressedEvent* event) {

}

void onKeyReleased(kat::KeyReleasedEvent* event) {
	if (event->getKey() == kat::Key::kEqual) {
		curT = (curT + 1) % 1024;
	}
	if (event->getKey() == kat::Key::kMinus) {
		curT = (curT - 1) % 1024;
	}

	if (event->getKey() == kat::Key::kRight) {
		curT = (curT + 1) % 1024;
	}
	if (event->getKey() == kat::Key::kLeft) {
		curT = (curT - 1) % 1024;
	}

	if (event->getKey() == kat::Key::kUp) {
		curT = (curT + 32) % 1024;
	}
	if (event->getKey() == kat::Key::kDown) {
		curT = (curT - 32) % 1024;
	}
}

void GameApp::create() {
	tileset = new kat::Tileset("terrain_atlas.png", 32);

	glm::vec4 uvs = tileset->getTile(0);
	//glm::vec4 uvs = { 0, 0, 1, 1 };

	vbo = new kat::VertexBuffer({ 
		-1, -1, 0, uvs.x, uvs.y,
		-0.9, -0.9, 0, uvs.z, uvs.w,
		-1, -0.9, 0, uvs.x, uvs.w,
		-0.9, -1, 0, uvs.z, uvs.y
	});

	kat::enableBlend();

	ebo = new kat::ElementBuffer({ 0, 1, 2, 0, 3, 1 });
	vao = new kat::VertexArray();
	vao->vbo(vbo, { 3, 2 });
	vao->attachEBO(ebo);

	shader = new kat::ShaderProgram({ new kat::Shader("main.frag.glsl", kat::ShaderType::eFragment), new kat::Shader("main.vert.glsl", kat::ShaderType::eVertex) });
	shader2 = new kat::ShaderProgram({ new kat::Shader("s2.frag.glsl", kat::ShaderType::eFragment), new kat::Shader("s2.vert.glsl", kat::ShaderType::eVertex) });

	chunkManager = new ChunkManager(tileset);
	camera = new Camera(0, 0, 800, 800);

	mainEventLayer = getEventHandler()->createLayer("main", 0);
	mainEventLayer->registerListener<kat::KeyPressedEvent>(kat::events::eKeyPressed, onKeyPressed);
	mainEventLayer->registerListener<kat::KeyReleasedEvent>(kat::events::eKeyReleased, onKeyReleased);
}



void GameApp::render() {
	if (getWindow()->getKey(GLFW_KEY_A)) {
		camera->translate(-4, 0);
	}

	if (getWindow()->getKey(GLFW_KEY_D)) {
		camera->translate(4, 0);
	}

	if (getWindow()->getKey(GLFW_KEY_W)) {
		camera->translate(0, 4);
	}

	if (getWindow()->getKey(GLFW_KEY_S)) {
		camera->translate(0, -4);
	}


	camera->update();


	kat::clearFrame(0, 0, 0);

	glm::vec2 mp = getWindow()->getMousePos();
	mp.x = mp.x + camera->getPos().x;
	mp.y = (800 - mp.y) + camera->getPos().y;
	
	mp.x = (mp.x / TILE_SIZE);
	mp.y = (mp.y / TILE_SIZE);
	if (mp.x < 0) { mp.x -= 1; }
	if (mp.y < 0) { mp.y -= 1; }


	if (getWindow()->getMouse(GLFW_MOUSE_BUTTON_1)) {
		chunkManager->setTile(mp, curT);
	}
	if (getWindow()->getMouse(GLFW_MOUSE_BUTTON_2)) {
		chunkManager->setTile(mp, -1);
	}


	shader->use();
	shader->uniform2f("uHighlightedTile", { (int)mp.x, (int)mp.y });
	shader->uniformMat4("uViewProj", camera->getCombined());
	chunkManager->draw(shader, camera->getPos());

	shader2->use();
	shader2->uniform1i("uTile", curT);
	shader2->uniform2f("uTileSize", { 1.0f / 32.0f, 1.0f / 32.0f });
	shader2->uniform1i("uRowSize", 32);
	tileset->bindTex();
	kat::drawElements(kat::DrawMode::Triangles, vao, 6);
}

void GameApp::destroy() {
	delete vbo;
	delete vao;
}

int main() {
	
	GameApp* app = new GameApp();
	app->launch();

	return 0;
}