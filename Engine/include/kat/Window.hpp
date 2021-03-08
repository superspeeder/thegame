#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <spdlog/fmt/ostr.h>
#include <cinttypes>

namespace kat {

	enum class GLFWClientAPI {
		OpenGL = GLFW_OPENGL_API,
		OpenGLES = GLFW_OPENGL_ES_API,
		None = GLFW_NO_API
	};

	enum class GLFWContextCreationAPI {
		Native = GLFW_NATIVE_CONTEXT_API,
		EGL = GLFW_EGL_CONTEXT_API,
		OSMesa = GLFW_OSMESA_CONTEXT_API
	};
	
	enum class GLFWRobustness {
		NoRobustness = GLFW_NO_ROBUSTNESS,
		NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
		LostContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET
	};

	enum class GLFWReleaseBehavior {
		Any = GLFW_ANY_RELEASE_BEHAVIOR,
		Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,
		None = GLFW_RELEASE_BEHAVIOR_NONE
	};

	enum class GLFWOpenGLProfile {
		Core = GLFW_OPENGL_CORE_PROFILE,
		Compat = GLFW_OPENGL_COMPAT_PROFILE,
		Any = GLFW_OPENGL_ANY_PROFILE
	};

	struct WindowSettings {
		std::string title = "Application";
		int32_t width = 0, height = 0;
		
		int32_t ogl_major = 1, ogl_minor = 0, monitor = 0;

		bool resizable = false, fullscreen = false, decorated = true, maximized = false, visible = true, focused = true, auto_iconify = true, floating = false, center_cursor = true,
			transparent_framebuffer = false, focus_on_show = true, scale_to_monitor = false, stereo = false, srgb_capable = true, doublebuffer = true, opengl_forward_compat = false, 
			opengl_debug_context = false, cocoa_retina_framebuffer = true, cocoa_graphics_switching = false;

		int32_t red_bits = 8, green_bits = 8, blue_bits = 8, alpha_bits = 8, depth_bits = 24, stencil_bits = 8,
			accum_red_bits = 0, accum_green_bits = 0, accum_blue_bits = 0, accum_alpha_bits = 0, aux_buffers = 0,
			samples = 0, refresh_rate = GLFW_DONT_CARE;

		GLFWClientAPI client_api = GLFWClientAPI::OpenGL;
		GLFWContextCreationAPI context_creation_api = GLFWContextCreationAPI::Native;
		GLFWRobustness context_robustness = GLFWRobustness::NoRobustness;
		GLFWReleaseBehavior context_release_behavior = GLFWReleaseBehavior::Any;
		GLFWOpenGLProfile opengl_profile = GLFWOpenGLProfile::Any;

		std::string cocoa_frame_name = "", x11_class_name = "", x11_instance_name = "";


	};

	extern bool isGLFWInit;

	void TryInitGLFW();
	void TerminateGLFW();

	class Window {
	private:
		GLFWwindow* m_Window;

		int32_t m_Width, m_Height;
		std::string m_Title;

	public:
		
		Window(WindowSettings settings);

		void destroy();

		bool shouldClose();

		void pollEvents();
		void swapBuffers();

		void makeContextCurrent();
	};
}

std::ostream& operator<<(std::ostream& os, const kat::GLFWClientAPI& c);
std::ostream& operator<<(std::ostream& os, const kat::GLFWContextCreationAPI& c);
std::ostream& operator<<(std::ostream& os, const kat::GLFWOpenGLProfile& c);
std::ostream& operator<<(std::ostream& os, const kat::GLFWReleaseBehavior& c);
std::ostream& operator<<(std::ostream& os, const kat::GLFWRobustness& c);


