#include "profiling_example.h"

#include <godot_cpp/core/class_db.hpp>
#include <thread>
#include <chrono>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
// #define ZoneScoped (void*)0
#endif

using namespace godot;

void ProfilingExample::_bind_methods() {
    ClassDB::bind_method(D_METHOD("run_cpp_sleeps", "usec"), &ProfilingExample::run_cpp_sleeps);
}

ProfilingExample::ProfilingExample() {
}

ProfilingExample::~ProfilingExample() {
}

void ProfilingExample::cpp_sleep1(int p_usec) {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    if (p_usec > 0) {
        std::this_thread::sleep_for(std::chrono::microseconds(p_usec));
    }
}

void ProfilingExample::cpp_sleep2(int p_usec) {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    if (p_usec > 0) {
        std::this_thread::sleep_for(std::chrono::microseconds(p_usec));
    }
}

void ProfilingExample::cpp_sleep3(int p_usec) {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    if (p_usec > 0) {
        std::this_thread::sleep_for(std::chrono::microseconds(p_usec));
    }
}

void ProfilingExample::run_cpp_sleeps(int p_usec) {
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif
    cpp_sleep1(p_usec);
    cpp_sleep2(p_usec);
    cpp_sleep3(p_usec);
}
