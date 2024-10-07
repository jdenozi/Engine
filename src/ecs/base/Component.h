#pragma once

#include "Types.h"

namespace ecs{
    struct Component{
        friend class Manager;
    public:
        Component() : m_entityID(){}
        virtual ~Component(){};
        inline const entityID getID() const{return m_entityID;}
    private:
        entityID m_entityID;
    };
}

class Component1: public ecs::Component{};

class Component2: public ecs::Component{};