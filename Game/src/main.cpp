#include <iostream>

#include "main.hpp"
#include <kat/renderer/Renderer.hpp>

GameApp::GameApp() {
	kat::ApplicationSettings settings{};
	settings.app_name = "Game";
	settings.app_version = GAME_VERSION;
	settings.windowSettings.title = settings.app_name + " " + settings.app_version;
	settings.windowSettings.width = 800;
	settings.windowSettings.height = 800;

	setSettings(settings);
}

void GameApp::render() {
	kat::clearFrame(1, 0, 0);
}

int main() {
	
	GameApp* app = new GameApp();
	app->launch();

	return 0;
}