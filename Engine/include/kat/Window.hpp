#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <spdlog/fmt/ostr.h>
#include <cinttypes>
#include <glm/glm.hpp>
#include <kat/Event.hpp>

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

    struct mods {
        bool control, shift, alt, super, capsLock, numLock;

        mods(const int mask);
    };

    enum class Key {
        kUnknown = GLFW_KEY_UNKNOWN,
        kSpace = GLFW_KEY_SPACE,
        kApostrophe = GLFW_KEY_APOSTROPHE,
        kComma = GLFW_KEY_COMMA,
        kMinus = GLFW_KEY_MINUS,
        kPeriod = GLFW_KEY_PERIOD,
        kSlash = GLFW_KEY_SLASH,
        k0 = GLFW_KEY_0,
        k1 = GLFW_KEY_1,
        k2 = GLFW_KEY_2,
        k3 = GLFW_KEY_3,
        k4 = GLFW_KEY_4,
        k5 = GLFW_KEY_5,
        k6 = GLFW_KEY_6,
        k7 = GLFW_KEY_7,
        k8 = GLFW_KEY_8,
        k9 = GLFW_KEY_9,
        kSemicolon = GLFW_KEY_SEMICOLON,
        kEqual = GLFW_KEY_EQUAL,
        kA = GLFW_KEY_A,
        kB = GLFW_KEY_B,
        kC = GLFW_KEY_C,
        kD = GLFW_KEY_D,
        kE = GLFW_KEY_E,
        kF = GLFW_KEY_F,
        kG = GLFW_KEY_G,
        kH = GLFW_KEY_H,
        kI = GLFW_KEY_I,
        kJ = GLFW_KEY_J,
        kK = GLFW_KEY_K,
        kL = GLFW_KEY_L,
        kM = GLFW_KEY_M,
        kN = GLFW_KEY_N,
        kO = GLFW_KEY_O,
        kP = GLFW_KEY_P,
        kQ = GLFW_KEY_Q,
        kR = GLFW_KEY_R,
        kS = GLFW_KEY_S,
        kT = GLFW_KEY_T,
        kU = GLFW_KEY_U,
        kV = GLFW_KEY_V,
        kW = GLFW_KEY_W,
        kX = GLFW_KEY_X,
        kY = GLFW_KEY_Y,
        kZ = GLFW_KEY_Z,
        kLeftBracket = GLFW_KEY_LEFT_BRACKET,
        kBackslash = GLFW_KEY_BACKSLASH,
        kRightBracket = GLFW_KEY_RIGHT_BRACKET,
        kGraveAccent = GLFW_KEY_GRAVE_ACCENT,
        kWorld1 = GLFW_KEY_WORLD_1,
        kWorld2 = GLFW_KEY_WORLD_2,
        kEscape = GLFW_KEY_ESCAPE,
        kEnter = GLFW_KEY_ENTER,
        kTab = GLFW_KEY_TAB,
        kBackspace = GLFW_KEY_BACKSPACE,
        kInsert = GLFW_KEY_INSERT,
        kDelete = GLFW_KEY_DELETE,
        kRight = GLFW_KEY_RIGHT,
        kLeft = GLFW_KEY_LEFT,
        kUp = GLFW_KEY_UP,
        kDown = GLFW_KEY_DOWN,
        kPageUp = GLFW_KEY_PAGE_UP,
        kPageDown = GLFW_KEY_PAGE_DOWN,
        kHome = GLFW_KEY_HOME,
        kEnd = GLFW_KEY_END,
        kCapsLock = GLFW_KEY_CAPS_LOCK,
        kScrollLock = GLFW_KEY_SCROLL_LOCK,
        kNumLock = GLFW_KEY_NUM_LOCK,
        kPrintScreen = GLFW_KEY_PRINT_SCREEN,
        kPause = GLFW_KEY_PAUSE,
        kF1 = GLFW_KEY_F1,
        kF2 = GLFW_KEY_F2,
        kF3 = GLFW_KEY_F3,
        kF4 = GLFW_KEY_F4,
        kF5 = GLFW_KEY_F5,
        kF6 = GLFW_KEY_F6,
        kF7 = GLFW_KEY_F7,
        kF8 = GLFW_KEY_F8,
        kF9 = GLFW_KEY_F9,
        kF10 = GLFW_KEY_F10,
        kF11 = GLFW_KEY_F11,
        kF12 = GLFW_KEY_F12,
        kF13 = GLFW_KEY_F13,
        kF14 = GLFW_KEY_F14,
        kF15 = GLFW_KEY_F15,
        kF16 = GLFW_KEY_F16,
        kF17 = GLFW_KEY_F17,
        kF18 = GLFW_KEY_F18,
        kF19 = GLFW_KEY_F19,
        kF20 = GLFW_KEY_F20,
        kF21 = GLFW_KEY_F21,
        kF22 = GLFW_KEY_F22,
        kF23 = GLFW_KEY_F23,
        kF24 = GLFW_KEY_F24,
        kF25 = GLFW_KEY_F25,
        kKP0 = GLFW_KEY_KP_0,
        kKP1 = GLFW_KEY_KP_1,
        kKP2 = GLFW_KEY_KP_2,
        kKP3 = GLFW_KEY_KP_3,
        kKP4 = GLFW_KEY_KP_4,
        kKP5 = GLFW_KEY_KP_5,
        kKP6 = GLFW_KEY_KP_6,
        kKP7 = GLFW_KEY_KP_7,
        kKP8 = GLFW_KEY_KP_8,
        kKP9 = GLFW_KEY_KP_9,
        kKPDecimal = GLFW_KEY_KP_DECIMAL,
        kKPDivide = GLFW_KEY_KP_DIVIDE,
        kKPMultiply = GLFW_KEY_KP_MULTIPLY,
        kKPSubtract = GLFW_KEY_KP_SUBTRACT,
        kKPAdd = GLFW_KEY_KP_ADD,
        kKPEnter = GLFW_KEY_KP_ENTER,
        kKPEqual = GLFW_KEY_KP_EQUAL,
        kLeftShift = GLFW_KEY_LEFT_SHIFT,
        kLeftControl = GLFW_KEY_LEFT_CONTROL,
        kLeftAlt = GLFW_KEY_LEFT_ALT,
        kLeftSuper = GLFW_KEY_LEFT_SUPER,
        kRightShift = GLFW_KEY_RIGHT_SHIFT,
        kRightControl = GLFW_KEY_RIGHT_CONTROL,
        kRightAlt = GLFW_KEY_RIGHT_ALT,
        kRightSuper = GLFW_KEY_RIGHT_SUPER,
        kMenu = GLFW_KEY_MENU
    };


	extern bool isGLFWInit;

	void TryInitGLFW();
	void TerminateGLFW();

	GLFWimage loadGLFWimage(std::string path);

	bool isExtensionSupported(std::string name);

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

		void setWindowShouldClose(bool val = true);
		void setWindowSize(int32_t w, int32_t h);

		glm::ivec2 getSize();
		glm::ivec4 getFrameSize();

		glm::ivec2 getFramebufferSize();

		glm::vec2 getContentScale();

		void setSizeLimits(int32_t minW, int32_t minH, int32_t maxW, int32_t maxH);
		void removeSizeLimits();

		void setAspectRatio(int32_t w, int32_t h);
		void removeAspectRatioLimit();

		void setPos(int32_t x, int32_t y);

		glm::ivec2 getPos();

		void setTitle(std::string title);

		void setIcon(std::vector<std::string> icon_paths);
		void revertIcon();

		GLFWmonitor* getMonitor();
		void setMonitorWindowless(int32_t id, int32_t width, int32_t height, int32_t refreshRate);

		void setMonitorWindowed(int32_t xpos, int32_t ypos, int32_t width, int32_t height);

		void iconify();
		void restore();

		bool isIconified();

		void maximize();
		bool isMaximized();

		void hide();
		void show();

		bool isVisible();

		void focus();
		bool isFocused();

		void requestAttention();

		bool isTransparent();

		void setOpacity(float val);

		float getOpacity();

		bool isHovered();
		bool isResizable();
		bool isDecorated();
		bool isAutoIconify();
		bool isFloating();
		bool isFocusOnShow();

		void setResizable(bool val = true);
		void setDecorated(bool val = true);
		void setAutoIconify(bool val = true);
		void setFloating(bool val = true);
		void setFocusOnShow(bool val = true);

		void swapInterval(int32_t interval);

		inline bool getKey(int32_t id) { return glfwGetKey(m_Window, id); };
        inline bool getKey(kat::Key k) { return glfwGetKey(m_Window, static_cast<int>(k)); };
        inline GLFWwindow* getHandle() { return m_Window; };

		inline glm::vec2 getMousePos() {
			glm::dvec2 mp; glfwGetCursorPos(m_Window, &mp.x, &mp.y); return { (float)mp.x, (float)mp.y };
		};

		inline bool getMouse(int32_t id) { return glfwGetMouseButton(m_Window, id); };

	};

    class WindowEvent : public kat::Event {
    protected:
        kat::Window* m_Window;

    public:
        inline WindowEvent(kat::EventType* eventType, kat::Window* window) : kat::Event(eventType) {
            m_Window = window;
        };

        inline Window* getWindow() { return m_Window; };
    };


    class WindowCloseEvent : public WindowEvent {
    private:
    public:
        WindowCloseEvent(kat::Window* window);
    };

    class WindowCreateEvent : public WindowEvent {
    private:
    public:
        WindowCreateEvent(kat::Window* window);
    };

    class WindowResizeEvent : public WindowEvent {
    private:
        uint32_t m_OldWidth, m_NewWidth, m_OldHeight, m_NewHeight;
    public:
        WindowResizeEvent(kat::Window* window, uint32_t oldWidth, uint32_t oldHeight, uint32_t newWidth, uint32_t newHeight);

        inline uint32_t getOldWidth() { return m_OldWidth; };
        inline uint32_t getOldHeight() { return m_OldHeight; };
        inline uint32_t getNewWidth() { return m_NewWidth; };
        inline uint32_t getNewHeight() { return m_NewHeight; };
    };

    class WindowIconifyEvent : public WindowEvent {
    private:
    public:
        WindowIconifyEvent(kat::Window* window);
    };

    class WindowMaximizeEvent : public WindowEvent {
    private:
    public:
        WindowMaximizeEvent(kat::Window* window);
    };

    enum class Button {
        Left = GLFW_MOUSE_BUTTON_LEFT,
        Right = GLFW_MOUSE_BUTTON_RIGHT,
        Middle = GLFW_MOUSE_BUTTON_MIDDLE,
        Button4 = GLFW_MOUSE_BUTTON_4,
        Button5 = GLFW_MOUSE_BUTTON_5,
        Button6 = GLFW_MOUSE_BUTTON_6,
        Button7 = GLFW_MOUSE_BUTTON_7,
        Button8 = GLFW_MOUSE_BUTTON_8
    };

    class MouseClickEvent : public WindowEvent {
    private:
        glm::vec2 m_MousePos;
        kat::Button m_Button;

    public:
        MouseClickEvent(kat::Window* window, glm::vec2 mousePos, int mouseButton);

        inline kat::Button getButton() { return m_Button; };
        inline glm::vec2 getMousePos() { return m_MousePos; };


    };

    class MouseEnterEvent : public WindowEvent {
    private:
        glm::vec2 m_MousePos;
    public:
        MouseEnterEvent(kat::Window* window, glm::vec2 mousePos);
        inline glm::vec2 getMousePos() { return m_MousePos; };

    };

    class MouseLeaveEvent : public WindowEvent {
    private:
        glm::vec2 m_MousePos;
    public:
        MouseLeaveEvent(kat::Window* window, glm::vec2 mousePos);
        inline glm::vec2 getMousePos() { return m_MousePos; };

    };




    class KeyPressedEvent : public WindowEvent {
    private:
        kat::Key m_Key;
        kat::mods m_Mods;

    public:
        KeyPressedEvent(kat::Window* window, int key, int mods_);

        inline kat::Key getKey() { return m_Key; };
        inline kat::mods getMods() { return m_Mods; };

    };

    class KeyReleasedEvent : public WindowEvent {
    private:
        kat::Key m_Key;
        kat::mods m_Mods;

    public:
        KeyReleasedEvent(kat::Window* window, int key, int mods_);

        inline kat::Key getKey() { return m_Key; };
        inline kat::mods getMods() { return m_Mods; };
    };

    class PathDropEvent : public WindowEvent {
    private:
        std::string m_Path;
    public:
        PathDropEvent(kat::Window* window, std::string path);

        inline std::string getPath() { return m_Path; };

    };

    class WindowFramebufferResizeEvent : public WindowEvent {
    private:
        uint32_t m_OldWidth, m_NewWidth, m_OldHeight, m_NewHeight;

    public:
        WindowFramebufferResizeEvent(kat::Window* window, uint32_t oldWidth, uint32_t oldHeight, uint32_t newWidth, uint32_t newHeight);

        inline uint32_t getOldWidth() { return m_OldWidth; };
        inline uint32_t getOldHeight() { return m_OldHeight; };
        inline uint32_t getNewWidth() { return m_NewWidth; };
        inline uint32_t getNewHeight() { return m_NewHeight; };

    };

    class WindowContentScaleEvent : public WindowEvent {
    private:
        float m_NewScale;
    public:
        WindowContentScaleEvent(kat::Window* window, float newScale);

        inline float getNewScale() { return m_NewScale; };

    };

    class WindowMoveEvent : public WindowEvent {
    private:
        glm::vec2 m_NewPos;
    public:
        WindowMoveEvent(kat::Window* window, glm::vec2 newPos);

        inline glm::vec2 getNewPos() { return m_NewPos; };

    };

    class WindowFocusEvent : public WindowEvent {
    private:
    public:
        WindowFocusEvent(kat::Window* window);

    };

    class WindowRefreshEvent : public WindowEvent {
    private:
    public:
        WindowRefreshEvent(kat::Window* window);

    };

    class ConfigureWindowHintsEvent;

    namespace events {
        extern kat::EventType* eConfigureWindowHints;
    }

    class ConfigureWindowHintsEvent : public Event {
    private:
    public:
        inline ConfigureWindowHintsEvent() : Event(events::eConfigureWindowHints) {};
    };

    namespace events {
        extern bool areWindowEventsInitialized;

        extern kat::EventType* eWindowClose;
        extern kat::EventType* eWindowCreate;
        extern kat::EventType* eWindowResize;
        extern kat::EventType* eWindowIconify;
        extern kat::EventType* eWindowMaximize;
        extern kat::EventType* eMouseClick;
        extern kat::EventType* eMouseEnter;
        extern kat::EventType* eMouseLeave;
        extern kat::EventType* eKeyPressed;
        extern kat::EventType* eKeyReleased;
        extern kat::EventType* ePathDropped;
        extern kat::EventType* eWindowFramebufferResized;
        extern kat::EventType* eWindowContentScale;
        extern kat::EventType* eWindowMove;
        extern kat::EventType* eWindowFocus;
        extern kat::EventType* eWindowRefresh;


        void initWindowEvents();

    };
}

std::ostream& operator<<(std::ostream& os, const kat::GLFWClientAPI& c);
std::ostream& operator<<(std::ostream& os, const kat::GLFWContextCreationAPI& c);
std::ostream& operator<<(std::ostream& os, const kat::GLFWOpenGLProfile& c);
std::ostream& operator<<(std::ostream& os, const kat::GLFWReleaseBehavior& c);
std::ostream& operator<<(std::ostream& os, const kat::GLFWRobustness& c);


