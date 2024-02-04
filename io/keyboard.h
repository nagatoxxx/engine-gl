#pragma once

#include <map>
namespace eng
{
class Keyboard;
}

class eng::Keyboard
{
public:
    Keyboard();
    ~Keyboard();

    bool isKeyPressed(int key) const;

    void setKeyState(int key, bool pressed);

private:
    std::map<int, bool> m_keyStates;
};
