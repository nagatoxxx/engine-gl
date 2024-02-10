#include "events.h"

using namespace eng;

Event::Event(EventType type) : m_type(type)
{
}

/* virtual */ Event::~Event()
{
}

/* -------------------------------------------------------------------------------- */

KeyboardEvent::KeyboardEvent(int key, int action) : Event(EventType::KeyboardType), m_key(key), m_action(action)
{
}

KeyboardEvent::~KeyboardEvent()
{
}

/* -------------------------------------------------------------------------------- */

MouseEvent::MouseEvent(double x, double y) : Event(EventType::MouseType), m_x(x), m_y(y)
{
}

MouseEvent::~MouseEvent()
{
}
