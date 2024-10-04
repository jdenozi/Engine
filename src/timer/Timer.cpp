#include "pch.h"
#include "Timer.h"

Timer::Timer():m_last_frame(), m_delta_time(){}

void Timer::tick() {
    m_delta_time = glfwGetTime() - m_last_frame;
    m_last_frame = glfwGetTime();
}

void Timer::init() {

};
