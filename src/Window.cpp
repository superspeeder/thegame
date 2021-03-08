#include "kat/Window.hpp"
#include <spdlog/spdlog.h>


bool kat::isGLFWInit = false;

void kat::TryInitGLFW() {
	if (!kat::isGLFWInit) {
		glfwInit();
		kat::isGLFWInit = true;
		spdlog::info("GLFW Initialized");
	}
}

void kat::TerminateGLFW() {
	if (kat::isGLFWInit) {
		glfwTerminate();
		kat::isGLFWInit = false;
		spdlog::info("GLFW Terminated");
	}
}

std::ostream& operator<<(std::ostream& os, const kat::GLFWClientAPI& c) {
	switch(c) {
	case kat::GLFWClientAPI::None:
		os << "None";
		break;
	case kat::GLFWClientAPI::OpenGL:
		os << "OpenGL";
		break;
	case kat::GLFWClientAPI::OpenGLES:
		os << "OpenGLES";
		break;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, const kat::GLFWContextCreationAPI& c) {
	switch(c) {
	case kat::GLFWContextCreationAPI::EGL:
		os << "EGL";
		break;
	case kat::GLFWContextCreationAPI::Native:
		os << "Native";
		break;
	case kat::GLFWContextCreationAPI::OSMesa:
		os << "OSMesa";
		break;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, const kat::GLFWOpenGLProfile& c) {
	switch(c) {
	case kat::GLFWOpenGLProfile::Any:
		os << "Any";
		break;
	case kat::GLFWOpenGLProfile::Compat:
		os << "Compat";
		break;
	case kat::GLFWOpenGLProfile::Core:
		os << "Core";
		break;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, const kat::GLFWReleaseBehavior& c) {
	switch(c) {
	case kat::GLFWReleaseBehavior::Any:
		os << "Any";
		break;
	case kat::GLFWReleaseBehavior::Flush:
		os << "Flush";
		break;
	case kat::GLFWReleaseBehavior::None:
		os << "None";
		break;
	}

	return os;
}
std::ostream& operator<<(std::ostream& os, const kat::GLFWRobustness& c) {
	switch(c) {
	case kat::GLFWRobustness::LostContextOnReset:
		os << "LoseContextOnReset";
		break;
	case kat::GLFWRobustness::NoResetNotification:
		os << "NoResetNotification";
		break;
	case kat::GLFWRobustness::NoRobustness:
		os << "NoRobustness";
		break;
	}
	return os;
}




kat::Window::Window(kat::WindowSettings settings) {
	kat::TryInitGLFW();


	glfwDefaultWindowHints();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.ogl_major);
	spdlog::debug("Window('{0}').contextVersionMajor = {1}", settings.title, settings.ogl_major);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.ogl_minor);
	spdlog::debug("Window('{0}').contextVersionMinor = {1}", settings.title, settings.ogl_minor);

	glfwWindowHint(GLFW_RESIZABLE, settings.resizable);
	spdlog::debug("Window('{0}').resizable = {1}", settings.title, settings.resizable);

	glfwWindowHint(GLFW_DECORATED, settings.decorated);
	spdlog::debug("Window('{0}').decorated = {1}", settings.title, settings.decorated);

	glfwWindowHint(GLFW_MAXIMIZED, settings.maximized);
	spdlog::debug("Window('{0}').maximized = {1}", settings.title, settings.maximized);

	glfwWindowHint(GLFW_VISIBLE, settings.visible);
	spdlog::debug("Window('{0}').visible = {1}", settings.title, settings.visible);

	glfwWindowHint(GLFW_AUTO_ICONIFY, settings.auto_iconify);
	spdlog::debug("Window('{0}').autoIconify = {1}", settings.title, settings.auto_iconify);

	glfwWindowHint(GLFW_FLOATING, settings.floating);
	spdlog::debug("Window('{0}').floating = {1}", settings.title, settings.floating);

	glfwWindowHint(GLFW_CENTER_CURSOR, settings.center_cursor);
	spdlog::debug("Window('{0}').centerCursor = {1}", settings.title, settings.center_cursor);

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, settings.transparent_framebuffer);
	spdlog::debug("Window('{0}').transparentFramebuffer = {1}", settings.title, settings.transparent_framebuffer);

	glfwWindowHint(GLFW_FOCUS_ON_SHOW, settings.focus_on_show);
	spdlog::debug("Window('{0}').focusOnShow = {1}", settings.title, settings.focus_on_show);

	glfwWindowHint(GLFW_SCALE_TO_MONITOR, settings.scale_to_monitor);
	spdlog::debug("Window('{0}').scaleToMonitor = {1}", settings.title, settings.scale_to_monitor);

	glfwWindowHint(GLFW_STEREO, settings.stereo);
	spdlog::debug("Window('{0}').stereo = {1}", settings.title, settings.stereo);

	glfwWindowHint(GLFW_SRGB_CAPABLE, settings.srgb_capable);
	spdlog::debug("Window('{0}').srgbCapable = {1}", settings.title, settings.srgb_capable);

	glfwWindowHint(GLFW_DOUBLEBUFFER, settings.doublebuffer);
	spdlog::debug("Window('{0}').doublebuffer = {1}", settings.title, settings.doublebuffer);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, settings.opengl_forward_compat);
	spdlog::debug("Window('{0}').openGLForwardCompat = {1}", settings.title, settings.opengl_forward_compat);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, settings.opengl_debug_context);
	spdlog::debug("Window('{0}').openGLDebugContext = {1}", settings.title, settings.opengl_debug_context);

	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, settings.cocoa_retina_framebuffer);
	spdlog::debug("Window('{0}').cocoaRetinaFramebuffer = {1}", settings.title, settings.cocoa_retina_framebuffer);

	glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, settings.cocoa_graphics_switching);
	spdlog::debug("Window('{0}').cocoaGraphicsSwitching = {1}", settings.title, settings.cocoa_graphics_switching);

	glfwWindowHint(GLFW_RED_BITS, settings.red_bits);
	spdlog::debug("Window('{0}').redBits = {1}", settings.title, settings.red_bits);

	glfwWindowHint(GLFW_GREEN_BITS, settings.green_bits);
	spdlog::debug("Window('{0}').greenBits = {1}", settings.title, settings.green_bits);

	glfwWindowHint(GLFW_BLUE_BITS, settings.blue_bits);
	spdlog::debug("Window('{0}').blueBits = {1}", settings.title, settings.blue_bits);

	glfwWindowHint(GLFW_ALPHA_BITS, settings.alpha_bits);
	spdlog::debug("Window('{0}').alphaBits = {1}", settings.title, settings.alpha_bits);

	glfwWindowHint(GLFW_DEPTH_BITS, settings.depth_bits);
	spdlog::debug("Window('{0}').depthBits = {1}", settings.title, settings.depth_bits);

	glfwWindowHint(GLFW_STENCIL_BITS, settings.stencil_bits);
	spdlog::debug("Window('{0}').stencilBits = {1}", settings.title, settings.stencil_bits);

	glfwWindowHint(GLFW_ACCUM_RED_BITS, settings.accum_red_bits);
	spdlog::debug("Window('{0}').accumRedBits = {1}", settings.title, settings.accum_red_bits);

	glfwWindowHint(GLFW_ACCUM_GREEN_BITS, settings.accum_green_bits);
	spdlog::debug("Window('{0}').accumGreenBits = {1}", settings.title, settings.accum_green_bits);

	glfwWindowHint(GLFW_ACCUM_BLUE_BITS, settings.accum_blue_bits);
	spdlog::debug("Window('{0}').accumBlueBits = {1}", settings.title, settings.accum_blue_bits);

	glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, settings.accum_alpha_bits);
	spdlog::debug("Window('{0}').accumAlphaBits = {1}", settings.title, settings.accum_alpha_bits);

	glfwWindowHint(GLFW_AUX_BUFFERS, settings.aux_buffers);
	spdlog::debug("Window('{0}').auxBuffers = {1}", settings.title, settings.aux_buffers);

	glfwWindowHint(GLFW_SAMPLES, settings.samples);
	spdlog::debug("Window('{0}').samples = {1}", settings.title, settings.samples);

	glfwWindowHint(GLFW_REFRESH_RATE, settings.refresh_rate);
	spdlog::debug("Window('{0}').refreshRate = {1}", settings.title, settings.refresh_rate);

	glfwWindowHint(GLFW_CLIENT_API, static_cast<int32_t>(settings.client_api));
	spdlog::debug("Window('{0}').clientApi = {1}", settings.title, settings.client_api);

	glfwWindowHint(GLFW_CONTEXT_CREATION_API, static_cast<int32_t>(settings.context_creation_api));
	spdlog::debug("Window('{0}').contextCreationApi = {1}", settings.title, settings.context_creation_api);

	glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, static_cast<int32_t>(settings.context_robustness));
	spdlog::debug("Window('{0}').contextRobustness = {1}", settings.title, settings.context_robustness);

	glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, static_cast<int32_t>(settings.context_release_behavior));
	spdlog::debug("Window('{0}').contextReleaseBehavior = {1}", settings.title, settings.context_release_behavior);

	glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int32_t>(settings.opengl_profile));
	spdlog::debug("Window('{0}').openGLProfile = {1}", settings.title, settings.opengl_profile);

	glfwWindowHintString(GLFW_COCOA_FRAME_NAME, settings.cocoa_frame_name.c_str());
	spdlog::debug("Window('{0}').cocoa_frame_name = \"{1}\"", settings.title, settings.cocoa_frame_name);
	
	glfwWindowHintString(GLFW_X11_CLASS_NAME, settings.x11_class_name.c_str());
	spdlog::debug("Window('{0}').x11_class_name = \"{1}\"", settings.title, settings.x11_class_name);
	
	glfwWindowHintString(GLFW_X11_INSTANCE_NAME, settings.x11_instance_name.c_str());
	spdlog::debug("Window('{0}').x11_instance_name = \"{1}\"", settings.title, settings.x11_instance_name);

	int c;
	GLFWmonitor* monitor = glfwGetMonitors(&c)[settings.monitor];
	const GLFWvidmode* vm = glfwGetVideoMode(monitor);

	if (settings.width < 1) { settings.width = vm->width; };
	if (settings.height < 1) { settings.height = vm->height; };

	spdlog::debug("Window('{0}').width = {1}", settings.title, settings.width);
	spdlog::debug("Window('{0}').height = {1}", settings.title, settings.height);
	spdlog::debug("Window('{0}').monitor = {1}", settings.title, settings.monitor);
	spdlog::debug("Window('{0}').fullscreen = {1}", settings.title, settings.fullscreen);

	if (settings.fullscreen) {
		m_Window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), monitor, NULL);
	}
	else {
		m_Window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), NULL, NULL);
	}
	spdlog::info("Created Window('{0}', {1} x {2})", settings.title, settings.width, settings.height);

	m_Title = settings.title;
	m_Width = settings.width;
	m_Height = settings.height;
}

void kat::Window::destroy() {
	glfwDestroyWindow(m_Window);
	spdlog::info("Destroyed Window('{0}')", m_Title);
}

bool kat::Window::shouldClose() {
	return glfwWindowShouldClose(m_Window);
}

void kat::Window::pollEvents() {
	glfwPollEvents();
}

void kat::Window::swapBuffers() {
	glfwSwapBuffers(m_Window);
}

void kat::Window::makeContextCurrent() {
	glfwMakeContextCurrent(m_Window);
	spdlog::debug("Made the context for Window('{0}') current", m_Title);
}


