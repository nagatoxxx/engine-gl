#include "object.h"

using namespace eng;

Object::Object(const std::string& filename, const std::string& name) : m_name(name), m_model(filename)
{
}

/* virtual */ Object::~Object()
{
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
