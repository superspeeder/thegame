#include "kat/Window.hpp"
#include <spdlog/spdlog.h>
#include <stb_image.h>

bool kat::isGLFWInit = false;

void kat::TryInitGLFW() {
	if (!kat::isGLFWInit) {
		glfwInit();
		kat::events::initWindowEvents();
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

void key_callback(GLFWwindow* window_, int key, int scancode, int action, int mods) {
	kat::Window* window = static_cast<kat::Window*>(glfwGetWindowUserPointer(window_));
	if (action == GLFW_PRESS) {
		kat::events::defaultEventHandler->queueEvent(new kat::KeyPressedEvent(window, key, mods));
	}
	else if (action == GLFW_RELEASE) {
		kat::events::defaultEventHandler->queueEvent(new kat::KeyReleasedEvent(window, key, mods));
	}
}

void bindGLFWEventCallbacks(GLFWwindow* window, kat::Window* windowO) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowUserPointer(window, (void*)windowO);
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

	bindGLFWEventCallbacks(m_Window, this);

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

void kat::Window::setWindowShouldClose(bool val) {
	glfwSetWindowShouldClose(m_Window, val);
}

void kat::Window::setWindowSize(int32_t w, int32_t h) {
	glfwSetWindowSize(m_Window, w, h);
	m_Width = w;
	m_Height = h;
}

glm::ivec2 kat::Window::getSize() {
	glm::ivec2 v = { 0, 0 };
	glfwGetWindowSize(m_Window, &v.x, &v.y);
	return v;
}

glm::ivec4 kat::Window::getFrameSize() {
	glm::ivec4 v = { 0, 0, 0, 0 };
	glfwGetWindowFrameSize(m_Window, &v.x, &v.y, &v.z, &v.w);
	return v;
}

glm::ivec2 kat::Window::getFramebufferSize() {
	glm::ivec2 v = { 0, 0 };
	glfwGetFramebufferSize(m_Window, &v.x, &v.y);
	return v;
}

glm::vec2 kat::Window::getContentScale() {
	glm::vec2 v = { 0.0f, 0.0f };
	glfwGetWindowContentScale(m_Window, &v.x, &v.y);
	return v;
}

void kat::Window::setSizeLimits(int32_t minW, int32_t minH, int32_t maxW, int32_t maxH) {
	glfwSetWindowSizeLimits(m_Window, minW, minH, maxW, maxH);
}

void kat::Window::removeSizeLimits() {
	setSizeLimits(GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void kat::Window::setAspectRatio(int32_t w, int32_t h) {
	glfwSetWindowAspectRatio(m_Window, w, h);
}

void kat::Window::removeAspectRatioLimit() {
	setAspectRatio(GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void kat::Window::setPos(int32_t x, int32_t y) {
	glfwSetWindowPos(m_Window, x, y);
}

glm::ivec2 kat::Window::getPos() {
	glm::ivec2 v = { 0, 0 };
	glfwGetWindowPos(m_Window, &v.x, &v.y);
	return v;
}

void kat::Window::setTitle(std::string title) {
	glfwSetWindowTitle(m_Window, title.c_str());
	m_Title = title;
}

GLFWimage kat::loadGLFWimage(std::string path) {
	int32_t c;
	GLFWimage img{};
	img.pixels = stbi_load(path.c_str(), &img.width, &img.height, &c, 4);
	return img;
}

void kat::Window::setIcon(std::vector<std::string> icon_paths) {
	std::vector<GLFWimage> icons;
	for (const std::string& path : icon_paths) {
		icons.push_back(kat::loadGLFWimage(path));
	}
	glfwSetWindowIcon(m_Window, icons.size(), icons.data());
}

void kat::Window::revertIcon() {
	glfwSetWindowIcon(m_Window, 0, NULL);
}

GLFWmonitor* kat::Window::getMonitor() {
	return glfwGetWindowMonitor(m_Window);
}

void kat::Window::setMonitorWindowless(int32_t id, int32_t width, int32_t height, int32_t refreshRate) {
	int32_t c = 0;
	GLFWmonitor** monitors = glfwGetMonitors(&c);
	if (id >= c) {
		spdlog::error("Monitor {0} doesn't exist. Defaulting to primary (0)", id);
		glfwSetWindowMonitor(m_Window, monitors[0], 0, 0, width, height, refreshRate);
	} else {
		glfwSetWindowMonitor(m_Window, monitors[id], 0, 0, width, height, refreshRate);
	}

}

void kat::Window::setMonitorWindowed(int32_t xpos, int32_t ypos, int32_t width, int32_t height) {
	glfwSetWindowMonitor(m_Window, NULL, xpos, ypos, width, height, 0);
}

void kat::Window::iconify() {
	glfwIconifyWindow(m_Window);
}

void kat::Window::restore() {
	glfwRestoreWindow(m_Window);
}

bool kat::Window::isIconified() {
	return glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED);
}

void kat::Window::maximize() {
	glfwMaximizeWindow(m_Window);
}

bool kat::Window::isMaximized() {
	return glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED);
}

void kat::Window::hide() {
	glfwHideWindow(m_Window);
}

void kat::Window::show() {
	glfwShowWindow(m_Window);
}

bool kat::Window::isVisible() {
	return glfwGetWindowAttrib(m_Window, GLFW_VISIBLE);
}

void kat::Window::focus() {
	glfwFocusWindow(m_Window);
}

bool kat::Window::isFocused() {
	return glfwGetWindowAttrib(m_Window, GLFW_FOCUSED);
}

void kat::Window::requestAttention() {
	glfwRequestWindowAttention(m_Window);
}

bool kat::Window::isTransparent() {
	return glfwGetWindowAttrib(m_Window, GLFW_TRANSPARENT_FRAMEBUFFER);
}

void kat::Window::setOpacity(float val) {
	glfwSetWindowOpacity(m_Window, val);
}

float kat::Window::getOpacity() {
	return glfwGetWindowOpacity(m_Window);
}

bool kat::Window::isHovered() {
	return glfwGetWindowAttrib(m_Window, GLFW_HOVERED);
}

bool kat::Window::isResizable() {
	return glfwGetWindowAttrib(m_Window, GLFW_RESIZABLE);
}

bool kat::Window::isDecorated() {
	return glfwGetWindowAttrib(m_Window, GLFW_DECORATED);
}

bool kat::Window::isAutoIconify() {
	return glfwGetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY);
}

bool kat::Window::isFloating() {
	return glfwGetWindowAttrib(m_Window, GLFW_FLOATING);
}

bool kat::Window::isFocusOnShow() {
	return glfwGetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW);
}

void kat::Window::setResizable(bool val) {
	glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, val);
}

void kat::Window::setDecorated(bool val) {
	glfwSetWindowAttrib(m_Window, GLFW_DECORATED, val);

}

void kat::Window::setAutoIconify(bool val) {
	glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, val);

}

void kat::Window::setFloating(bool val) {
	glfwSetWindowAttrib(m_Window, GLFW_FLOATING, val);

}

void kat::Window::setFocusOnShow(bool val) {
	glfwSetWindowAttrib(m_Window, GLFW_FOCUS_ON_SHOW, val);
}

void kat::Window::swapInterval(int32_t interval) {
	glfwSwapInterval(interval);
}


bool kat::isExtensionSupported(std::string name) {
	return glfwExtensionSupported(name.c_str());
}

kat::WindowCloseEvent::WindowCloseEvent(kat::Window* window) : kat::WindowEvent(kat::events::eWindowClose, window) {
}

kat::WindowCreateEvent::WindowCreateEvent(kat::Window* window) : kat::WindowEvent(kat::events::eWindowCreate, window) {
}

kat::WindowResizeEvent::WindowResizeEvent(kat::Window* window, uint32_t oldWidth, uint32_t oldHeight, uint32_t newWidth, uint32_t newHeight) : kat::WindowEvent(kat::events::eWindowResize, window) {
	m_OldWidth = oldWidth; m_OldHeight = oldHeight;
	m_NewWidth = newWidth; m_NewHeight = newHeight;
}

kat::WindowIconifyEvent::WindowIconifyEvent(kat::Window* window) : kat::WindowEvent(kat::events::eWindowIconify, window) {
}

kat::WindowMaximizeEvent::WindowMaximizeEvent(kat::Window* window) : kat::WindowEvent(kat::events::eWindowMaximize, window) {
}

kat::MouseClickEvent::MouseClickEvent(kat::Window* window, glm::vec2 mousePos, int mouseButton) : kat::WindowEvent(kat::events::eMouseClick, window) {
	m_MousePos = mousePos;
	m_Button = static_cast<kat::Button>(mouseButton);
}

kat::MouseEnterEvent::MouseEnterEvent(kat::Window* window, glm::vec2 mousePos) : kat::WindowEvent(kat::events::eMouseEnter, window) {
	m_MousePos = mousePos;
}

kat::MouseLeaveEvent::MouseLeaveEvent(kat::Window* window, glm::vec2 mousePos) : kat::WindowEvent(kat::events::eMouseLeave, window) {
	m_MousePos = mousePos;
}

kat::KeyPressedEvent::KeyPressedEvent(kat::Window* window, int key, int mods_) : m_Mods(mods_), kat::WindowEvent(kat::events::eKeyPressed, window) {
	m_Key = static_cast<kat::Key>(key);
}

kat::KeyReleasedEvent::KeyReleasedEvent(kat::Window* window, int key, int mods_) : m_Mods(mods_), kat::WindowEvent(kat::events::eKeyReleased, window) {
	m_Key = static_cast<kat::Key>(key);
}

kat::PathDropEvent::PathDropEvent(kat::Window* window, std::string path) : kat::WindowEvent(kat::events::ePathDropped, window) {
	m_Path = path;
}

kat::WindowFramebufferResizeEvent::WindowFramebufferResizeEvent(kat::Window* window, uint32_t oldWidth, uint32_t oldHeight, uint32_t newWidth, uint32_t newHeight) : kat::WindowEvent(kat::events::eWindowFramebufferResized, window) {
	m_OldWidth = oldWidth; m_OldHeight = oldHeight;
	m_NewWidth = newWidth; m_NewHeight = newHeight;
}

kat::WindowContentScaleEvent::WindowContentScaleEvent(kat::Window* window, float newScale) : kat::WindowEvent(kat::events::eWindowContentScale, window) {
	m_NewScale = newScale;
}

kat::WindowMoveEvent::WindowMoveEvent(kat::Window* window, glm::vec2 newPos) : kat::WindowEvent(kat::events::eWindowMove, window) {
	m_NewPos = newPos;
}

kat::WindowFocusEvent::WindowFocusEvent(kat::Window* window) : kat::WindowEvent(kat::events::eWindowFocus, window) {
}

kat::WindowRefreshEvent::WindowRefreshEvent(kat::Window* window) : kat::WindowEvent(kat::events::eWindowRefresh, window) {
}

kat::mods::mods(const int mask) {
	control = mask & GLFW_MOD_CONTROL;
	shift = mask & GLFW_MOD_SHIFT;
	alt = mask & GLFW_MOD_ALT;
	super = mask & GLFW_MOD_SUPER;
	capsLock = mask & GLFW_MOD_CAPS_LOCK;
	numLock = mask & GLFW_MOD_NUM_LOCK;
}

namespace kat {
	namespace events {
		bool areWindowEventsInitialized = false;

		kat::EventType* eWindowClose;
		kat::EventType* eWindowCreate;
		kat::EventType* eWindowResize;
		kat::EventType* eWindowIconify;
		kat::EventType* eWindowMaximize;
		kat::EventType* eMouseClick;
		kat::EventType* eMouseEnter;
		kat::EventType* eMouseLeave;
		kat::EventType* eKeyPressed;
		kat::EventType* eKeyReleased;
		kat::EventType* ePathDropped;
		kat::EventType* eWindowFramebufferResized;
		kat::EventType* eWindowContentScale;
		kat::EventType* eWindowMove;
		kat::EventType* eWindowFocus;
		kat::EventType* eWindowRefresh;
		kat::EventType* eConfigureWindowHints;
	}
}

void kat::events::initWindowEvents() {
	if (!areWindowEventsInitialized) {
		eWindowClose = new kat::EventType("kat::window_close");
		eWindowCreate = new kat::EventType("kat::window_create");
		eWindowResize = new kat::EventType("kat::window_resize");
		eWindowIconify = new kat::EventType("kat::window_iconify");
		eWindowMaximize = new kat::EventType("kat::window_maximize");
		eMouseClick = new kat::EventType("kat::mouse_click");
		eMouseEnter = new kat::EventType("kat::mouse_enter");
		eMouseLeave = new kat::EventType("kat::mouse_leave");
		eKeyPressed = new kat::EventType("kat::key_pressed");
		eKeyReleased = new kat::EventType("kat::key_released");
		ePathDropped = new kat::EventType("kat::path_dropped");
		eWindowFramebufferResized = new kat::EventType("kat::window_framebuffer_resized");
		eWindowContentScale = new kat::EventType("kat::window_content_scale");
		eWindowMove = new kat::EventType("kat::window_move");
		eWindowFocus = new kat::EventType("kat::window_focus");
		eWindowRefresh = new kat::EventType("kat::window_refresh");
		eConfigureWindowHints = new kat::EventType("kat::configure_window_hints");
		areWindowEventsInitialized = true;
	}
}
