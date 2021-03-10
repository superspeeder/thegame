#include "kat/Event.hpp"

#include "kat/Window.hpp"
#include <imgui.h>

namespace kat {
    namespace events {
        kat::EventHandler* defaultEventHandler = nullptr;
    }
}

void postAll(kat::EventHandler* eh, kat::EventType* et) {
    for (kat::Event* e : et->getQueuedEvents()) {
        eh->postEvent(e);
    }

    et->clearQueue();
}


void kat::EventHandler::playEvents() {
    ImGuiIO& io = ImGui::GetIO();

    if (!io.WantCaptureMouse) {
        postAll(this, kat::events::eMouseClick);
    }

    if (!io.WantCaptureKeyboard) {
        postAll(this, kat::events::eKeyPressed);
        postAll(this, kat::events::eKeyReleased);
    }
}

void kat::EventType::postEvent(Event* event) {
    for (std::function<void(Event*)> eventListener : m_EventListeners) {
        eventListener(event);
        if (event->isHandled()) {
            break;
        }
    }
};
