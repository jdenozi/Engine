#include <iostream>
#include "engine/Engine.h"
#include "timer/Timer.h"
#include "events/Events.h"
#include "pch.h"
#include "ecs/base/Component.h"
#include "ecs/base/Types.h"
#include "utility/Logger.h"

int main() {

    auto id1 = ecs::ComponentType<Component1>();
    auto id2 = ecs::ComponentType<Component1>();
    auto id3 = ecs::ComponentType<Component2>();
    auto  c = Component2();
    LOG_INFO(fmt::format("result: {:d}", c.getID()));

    EngineCore.init();
    PoolEvent.init();
    BaseTimer.init();

    while(EngineCore.isRunning()){
        EngineCore.update();
        PoolEvent.polls();
        BaseTimer.tick();
    }

    return EXIT_SUCCESS;
}
