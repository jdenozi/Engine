#pragma once

#include <memory>
#include "pch.h"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;

class Engine {
public:
    Engine(const Engine&)=delete;

    Engine&operator=(const Engine&) =delete;
    ~Engine();

    static Engine &getInstance(){
        static Engine ref;
        return ref;
};

    void exit();

    void update();

    void init();

    [[nodiscard]] inline bool isRunning() const {
        return m_running;
    };

    inline std::shared_ptr<GLFWwindow> &window() {
        return m_window;
    };

    [[nodiscard]] inline int width() const {
        return m_width;
    };

    [[nodiscard]] inline int height() const {
        return m_height;
    };

private:
    Engine();
    bool m_running{};
    std::shared_ptr<GLFWwindow> m_window{};
    int m_width{}, m_height{};

};

static Engine& EngineCore = Engine::getInstance();
