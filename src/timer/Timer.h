#pragma once

class Timer {

public:

    Timer(const Timer &) = delete;

    Timer &operator=(const Timer &) = delete;

    static Timer &getInstance() {
        static Timer ref;
        return ref;
    }

    void tick();

    void init();

    [[nodiscard]] inline float deltaTime() const{return m_delta_time;}

private:
    Timer();
    float m_last_frame{}, m_delta_time{};


};

static Timer &BaseTimer = Timer::getInstance();
