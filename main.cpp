#include <iostream>
#include "engine/Engine.h"
#include "timer/Timer.h"
#include "events/Events.h"
#include "pch.h"
#include "ecs/base/components/Component.h"
#include "ecs/base/Types.h"

int main() {

    auto id1 = ecs::ComponentType<Component1>();
    auto id2 = ecs::ComponentType<Component1>();
    auto id3 = ecs::ComponentType<Component2>();


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
