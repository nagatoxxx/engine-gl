#pragma once

#include <memory>
#include <unordered_map>

#include "object.h"

namespace eng
{
class World;
}

class eng::World
{
public:
    World();
    virtual ~World();

    std::shared_ptr<Object> getObject(std::string name) const
    {
        return m_objects.at(name);
    }

    void addObject(Object&& obj)
    {
        m_objects.emplace(obj.getName(), std::make_shared<Object>(obj));
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Object>> m_objects;
};
