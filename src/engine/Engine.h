#pragma once

#include <GL/glew.h>
#include <glfw3.h>
#include <bits/fs_fwd.h>
#include <filesystem>

class Engine {
public:
    Engine();

    Engine(const Engine&)=delete;

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

    [[nodiscard]] inline float width() const {
        return m_width;
    };

    [[nodiscard]] inline float height() const {
        return m_height;
    };

private:
    bool m_running{};
    std::shared_ptr<GLFWwindow> m_window{};
    float m_width{}, m_height{};

};

static Engine& EngineCore = Engine::getInstance();
