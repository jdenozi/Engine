#include <iostream>
#include "engine/Engine.h"
#include "timer/Timer.h"
#include "events/Events.h"
#include "pch.h"
#include "ecs/base/Component.h"
#include "ecs/base/Types.h"
#include "utility/Logger.h"
#include "ecs/base/EntityManager.h"

int main() {

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
