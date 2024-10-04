#include <iostream>
#include "engine/Engine.h"
#include "timer/Timer.h"
#include "events/Events.h"
#include "pch.h"

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
