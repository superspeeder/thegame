#include "kat/Application.hpp"
#include <kat/renderer/Renderer.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


kat::Application::Application() {
}

void kat::Application::setSettings(kat::ApplicationSettings settings) {
	m_Settings = settings;
}

void kat::Application::launch() {
	initLogger();
	spdlog::info("Hello!");

	spdlog::info("Beginning Application Setup");
	
	createWindow();
	m_Window->makeContextCurrent();
	kat::initGLAD();


	spdlog::info("Starting Mainloop");
	while (keepRunning()) {
		mainloop_iter();
	}
	spdlog::info("Mainloop Ended");
	
	destroyWindow();
	spdlog::info("Goodbye!");
}

void kat::Application::createWindow() {
	m_Window = new kat::Window(m_Settings.windowSettings);
}

void kat::Application::destroyWindow() {
	m_Window->destroy();
	kat::TerminateGLFW();
}

bool kat::Application::keepRunning() {
	return !m_Window->shouldClose();
}

void kat::Application::mainloop_iter() {
	m_Window->pollEvents();
	render();

	m_Window->swapBuffers();

}

void kat::Application::render() {

}

void kat::Application::initLogger() {
	auto logger = spdlog::stdout_color_mt("main",spdlog::color_mode::always);
#ifdef KAT_DEBUG
	logger->set_level(spdlog::level::debug);
#else
	logger->set_level(spdlog::level::info);
#endif
	spdlog::set_default_logger(logger);
}