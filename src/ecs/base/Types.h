#pragma once

#include <cstdio>
#include <set>
#include <concepts>
#include "utility/Logger.h"
#include <fmt/format.h>

namespace ecs {

    class System;

    class Component;

    template<typename T> concept IsComponent = requires (T &){
        {std::is_same<T, Component>::value || std::is_base_of<T, Component>::value};
    };

    template<typename T> concept IsSystem = requires (T &){
        {std::is_same<T, System>::value || std::is_base_of<T, System>::value};
    };

    const size_t MAX_ENTITY_COUNT = 5000;
    const size_t MAX_COMPONENT_COUNT = 32;

    using EntityID = size_t;
    using SystemTypeID = size_t;
    using ComponentTypeID = size_t;
    using EntitySignature = std::set<ComponentTypeID>;

    inline static ComponentTypeID getRuntimeComponentTypeID() {
        static ComponentTypeID typeID = 0u;
        LOG_DEBUG(fmt::format("ID debug= {:d}", typeID));
        return typeID++;
    }

    inline static SystemTypeID getRuntimeSystemTypeID() {
        static SystemTypeID typeID = 0u;
        return typeID++;
    };

    template<typename T> requires IsComponent<T>
    inline static ComponentTypeID ComponentType() noexcept {
        static ComponentTypeID typeID = getRuntimeComponentTypeID();
        LOG_DEBUG(fmt::format("ID= {:d}", typeID));
        return typeID;
    }

    template<typename T> requires IsSystem<T>
    inline static ComponentTypeID SystemType() noexcept {
        static ComponentTypeID typeID = getRuntimeSystemTypeID();
        LOG_DEBUG(fmt::format("ID= {:d}", typeID));
        return typeID;
    }
}