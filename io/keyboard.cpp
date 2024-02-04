#include "keyboard.h"
#include "../utility/logger.h"

using namespace eng;

Keyboard::Keyboard() : m_keyStates()
{
    for (int i = 32; i <= 348; i++) { // 348 is the last key in the enum
        m_keyStates[i] = false;
    }

    Logger::log("Keyboard created");
}

Keyboard::~Keyboard()
{
    Logger::log("Keyboard destroyed");
}

bool Keyboard::isKeyPressed(int key) const
{
    return m_keyStates.at(key);
}

void Keyboard::setKeyState(int key, bool pressed)
{
    m_keyStates[key] = pressed;
}
