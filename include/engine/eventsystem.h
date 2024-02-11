#pragma once

#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <vector>

#include "events.h"

namespace eng
{
class EventSystem;
}

class eng::EventSystem
{
    using EventCallback = std::function<void(std::shared_ptr<Event>)>;

public:
    EventSystem() = delete;

    static void registerEventCallback(EventType type, EventCallback callback);
    static void pollEvents();
    template <typename T>
    static void sendEvent(const Event& e)
    {
        m_events.push(std::make_shared<T>(static_cast<const T&>(e)));
    }

private:
    static std::queue<std::shared_ptr<Event>>              m_events;
    static std::map<EventType, std::vector<EventCallback>> m_callbacks;
};
