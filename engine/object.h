#pragma once

#include "model.h"

namespace eng
{
class Object;
}

class eng::Object
{
public:
    Object();
    Object(const std::string& name, const std::string& filename);
    virtual ~Object();

    const std::string& getName() const;
    Model&             model();

    virtual void render();

private:
    std::string m_name;
    Model       m_model;
};
