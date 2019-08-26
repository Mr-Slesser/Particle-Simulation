#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <thread>
#include <chrono>

namespace Utils
{
class Timer
{
    bool ended = false;

public:
    void setTimeout(std::function<void()> function, int delay);
    void setInterval(std::function<void()> function, int interval);
    void end();
    bool hasEnded();
};
} // namespace Utils

#endif /* TIMER_H */
