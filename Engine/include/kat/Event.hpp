#pragma once
#include <string>
#include <functional>
#include <vector>
#include <type_traits>
#include <unordered_map>
#include <set>
#include <iostream>


namespace kat {

    class Event;

    class EventType {
    private:
        std::string m_DebugName;

        std::vector<std::function<void(Event*)> > m_EventListeners;
        std::vector<Event*> m_QueuedEvents;

    public:

        inline EventType(std::string debugName) {
            m_DebugName = debugName;
        };

        inline std::string getDebugName() {
            return m_DebugName;
        };

        void postEvent(Event* event);

        inline void registerListener_Front(std::function<void(Event*)> listener) {
            m_EventListeners.insert(m_EventListeners.begin(), listener);
        };

        inline void registerListener_Back(std::function<void(Event*)> listener) {
            m_EventListeners.push_back(listener);
        };

        inline void queueEvent(Event* e) { m_QueuedEvents.push_back(e); };

        inline std::vector<Event*> getQueuedEvents() { return m_QueuedEvents; };

        inline void clearQueue() { m_QueuedEvents.clear(); };
    };

    class Event {
    private:
        bool m_IsHandled;

        EventType *m_Type;
    public:

        inline Event(EventType* type) {
            m_IsHandled = false;
            m_Type = type;
        };

        inline bool isHandled() {
            return m_IsHandled;
        };

        inline const void setHandled() {
            m_IsHandled = true;
        };

        inline EventType* getEventType() {
            return m_Type;
        };
    };

    class EventLayer {
    private:
        std::string m_DebugName;
        int m_Index;
        std::unordered_map<EventType*, std::vector<std::function<void(Event*)> > > m_EventListeners;

    public:

        inline EventLayer(std::string debugName, int index) {
            m_DebugName = debugName;
            m_Index = index;
        };
        
        inline int getIndex() {
            return m_Index;
        };

        template <class _EventClass>
        inline void registerListener(EventType* eventType, const std::function<void(_EventClass* event)> eventCallback) {
            if (m_EventListeners.find(eventType) != m_EventListeners.end()) {
                m_EventListeners[eventType] = std::vector<std::function<void(Event*)> >();
            }
            m_EventListeners[eventType].push_back([eventCallback](kat::Event* evt) {
                _EventClass* event = reinterpret_cast<_EventClass*>(evt);
                eventCallback(event);
            });
        };

        inline void postEvent(Event* event) {
            if (m_EventListeners.find(event->getEventType()) == m_EventListeners.end()) return;
            for (std::function<void(Event*)> callback : m_EventListeners[event->getEventType()]) {
                callback(event);
            }
        };
    };

    struct elayer_comparator {
        inline bool operator() (EventLayer* a, EventLayer* b) const {
            return a->getIndex() > b->getIndex();
        };
    };

    class EventHandler {
    private:
        std::multiset<EventLayer*, elayer_comparator> m_Layers;

    public:

        inline EventHandler() { };

        inline EventLayer* createLayer(std::string debugName, int index) {
            EventLayer* l = new EventLayer(debugName, index);
            pushLayer(l);
            return l;
        };

        inline void pushLayer(EventLayer* elayer) {
            m_Layers.insert(elayer);
        };

        inline void postEvent(Event* event) {
            for (EventLayer* layer : m_Layers) {
                layer->postEvent(event);
                if (event->isHandled()) {
                    break;
                }
            }
        };

        inline void queueEvent(Event* event) {
            event->getEventType()->queueEvent(event);
        }

        void playEvents();
    };

    namespace events {
        extern kat::EventHandler* defaultEventHandler;
    }
}