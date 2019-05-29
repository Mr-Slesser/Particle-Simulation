#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <thread>
#include <chrono>

namespace Utils
{
    class Timer {
        bool ended = false;

        public:
            void setTimeout(auto function, int delay);
            void setInterval(auto function, int interval);
            void end();
    };

    void Timer::setTimeout(auto function, int delay) {
        ended = false;
        std::thread t([=]() {
            if(ended) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            if(ended) return;
            function();
        });
        t.detach();
    }

    void Timer::setInterval(auto function, int interval) {
        ended = false;
        std::thread t([=]() {
            while(true) {
                if(ended) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                if(ended) return;
                function();
            }
        });
        t.detach();
    }

    void Timer::end() {
        ended = true;
    }
} // namespace Utils

#endif /* TIMER_HPP */
