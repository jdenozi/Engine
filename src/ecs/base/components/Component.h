#pragma once

namespace ecs{
    struct Component{

    public:
        virtual ~Component(){};
    };
}

class Component1: public ecs::Component{};

class Component2: public ecs::Component{};