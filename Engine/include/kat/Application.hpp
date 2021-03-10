#pragma once

#include <string>
#include <cinttypes>

#include "kat/renderer/Renderer.hpp"
#include "kat/Window.hpp"

#include "kat/Event.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace kat {

	struct ApplicationSettings {
		std::string app_name = "Application";
		std::string app_version = "0.1.0";

		kat::WindowSettings windowSettings{};
	};

	class Application {
	private:
		ApplicationSettings m_Settings;
		kat::Window* m_Window;
		kat::EventHandler* m_EventHandler;


		void createWindow();
		void destroyWindow();

		void mainloop_iter();
		
		bool keepRunning();

		void initLogger();

	protected:
		void setSettings(ApplicationSettings settings);

		virtual void render();
		virtual void create();
		virtual void destroy();

	public:

		Application();


		void launch();

		std::string getApplicationName();
		std::string getApplicationVersion();
		kat::Window* getWindow();


		inline kat::EventHandler* getEventHandler() {
			return m_EventHandler;
		};
	};
}