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

    using entityId = size_t;
    using systemTypeId = size_t;
    using componentTypeId = size_t;
    using entitySignature = std::set<componentTypeId>;

    inline static componentTypeId getRuntimeComponentTypeID() {
        static componentTypeId typeID = 0u;
        return typeID++;
    }

    inline static systemTypeId getRuntimeSystemTypeID() {
        static systemTypeId typeID = 0u;
        return typeID++;
    };

    template<typename T> requires IsComponent<T>
    inline static componentTypeId ComponentType() noexcept {
        static componentTypeId typeID = getRuntimeComponentTypeID();
        LOG_DEBUG(fmt::format("ID= {:d}", typeID));
        return typeID;
    }

    template<typename T> requires IsSystem<T>
    inline static componentTypeId SystemType() noexcept {
        static componentTypeId typeID = getRuntimeSystemTypeID();
        LOG_DEBUG(fmt::format("ID= {:d}", typeID));
        return typeID;
    }
}