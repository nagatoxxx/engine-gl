#include "object.h"
#include "../utility/logger.h"

using namespace eng;

Object::Object() : m_name("object"), m_model()
{
    Logger::log("Object created: " + m_name);
}

Object::Object(const std::string& name, const std::string& filename) : m_name(name), m_model(filename)
{
    Logger::log("Object created: " + m_name);
}

/* virtual */ Object::~Object()
{
    Logger::log("Object destroyed: " + m_name);
}

const std::string& Object::getName() const
{
    return m_name;
}

Model& Object::model()
{
    return m_model;
}

/* virtual */ void Object::render()
{
    m_model.render();
}
