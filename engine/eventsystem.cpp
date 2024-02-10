#include "eventsystem.h"

using namespace eng;

// static EventSystem members initialization;
std::queue<std::shared_ptr<Event>>                           EventSystem::m_events;
std::map<EventType, std::vector<EventSystem::EventCallback>> EventSystem::m_callbacks;

/* static */ void EventSystem::registerEventCallback(EventType type, EventCallback callback)
{
    m_callbacks[type].push_back(callback);
}

/* static */ void EventSystem::pollEvents()
{
    while (!m_events.empty()) {
        std::shared_ptr<Event> e = m_events.front();
        for (EventCallback callback : m_callbacks[e->type()]) {
            callback(e);
        }
        m_events.pop();
    }
}
