#include "kat/Application.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


kat::Application::Application() {
	m_EventHandler = new kat::EventHandler();
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_Window->getHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 450");

	create();

	spdlog::info("Starting Mainloop");
	while (keepRunning()) {
		mainloop_iter();
	}
	spdlog::info("Mainloop Ended");
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	destroy();
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

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Render();
	m_EventHandler->playEvents();

	render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	m_Window->swapBuffers();

}

void kat::Application::render() {

}

void kat::Application::create() {

}

void kat::Application::destroy() {

}

kat::Window* kat::Application::getWindow() {
	return m_Window;
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