#include <iostream>
#include "engine/Engine.h"
#include "pch.h"

int main() {
    EngineCore.init();

    while(EngineCore.isRunning()){
        EngineCore.update();
    }

    return 0;
}
