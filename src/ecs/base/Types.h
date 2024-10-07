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

    using entityID = size_t;
    using systemTypeID = size_t;
    using componentTypeID = size_t;
    using entitySignature = std::set<componentTypeID>;

    inline static componentTypeID getRuntimeComponentTypeID() {
        static componentTypeID typeID = 0u;
        LOG_DEBUG(fmt::format("ID debug= {:d}", typeID));
        return typeID++;
    }

    inline static systemTypeID getRuntimeSystemTypeID() {
        static systemTypeID typeID = 0u;
        return typeID++;
    };

    template<typename T> requires IsComponent<T>
    inline static componentTypeID ComponentType() noexcept {
        static componentTypeID typeID = getRuntimeComponentTypeID();
        LOG_DEBUG(fmt::format("ID= {:d}", typeID));
        return typeID;
    }

    template<typename T> requires IsSystem<T>
    inline static componentTypeID SystemType() noexcept {
        static componentTypeID typeID = getRuntimeSystemTypeID();
        LOG_DEBUG(fmt::format("ID= {:d}", typeID));
        return typeID;
    }
}