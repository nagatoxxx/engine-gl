#pragma once

namespace eng
{
enum EventType
{
    KeyboardType = 0,
    MouseType,
    CustomType
};

class Event;
class KeyboardEvent;
class MouseEvent;
} // namespace eng

class eng::Event
{
public:
    Event(EventType type);
    virtual ~Event() = 0;

    EventType type() const
    {
        return m_type;
    }

private:
    EventType m_type;
};

class eng::KeyboardEvent : public eng::Event
{
public:
    KeyboardEvent(int key, int action);
    ~KeyboardEvent();

    int key() const
    {
        return m_key;
    }
    int action() const
    {
        return m_action;
    }

private:
    int m_key;
    int m_action;
};

class eng::MouseEvent : public eng::Event
{
public:
    MouseEvent(double x, double y);
    ~MouseEvent();

    double x() const
    {
        return m_x;
    }
    double y() const
    {
        return m_y;
    }

private:
    double m_x, m_y;
};
