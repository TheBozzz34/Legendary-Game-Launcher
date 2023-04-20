#pragma once

#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>

template<std::intmax_t FPS>
class frame_rater {
public:
    frame_rater() :                 // initialize the object keeping the pace
        time_between_frames{ 1 },     // std::ratio<1, FPS> seconds
        tp{ std::chrono::steady_clock::now() }
    {}

    void sleep() {
        // add to time point
        tp += time_between_frames;

        // and sleep until that time point
        std::this_thread::sleep_until(tp);
    }

private:
    // a duration with a length of 1/FPS seconds
    std::chrono::duration<double, std::ratio<1, FPS>> time_between_frames;

    // the time point we'll add to in every loop
    std::chrono::time_point<std::chrono::steady_clock, decltype(time_between_frames)> tp;
};