#pragma once

#include <string>
#include <cinttypes>

#include "kat/Window.hpp"


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


		void createWindow();
		void destroyWindow();

		void mainloop_iter();
		
		bool keepRunning();

		void initLogger();

	protected:
		void setSettings(ApplicationSettings settings);

		virtual void render();

	public:

		Application();


		void launch();

		std::string getApplicationName();
		std::string getApplicationVersion();

	};
}