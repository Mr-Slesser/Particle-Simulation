#include "PCHeader.h"
#include "Timer.h"

namespace Utils
{
void Timer::setTimeout(std::function<void()> function, int delay)
{
    ended = false;
    std::thread t([=]() {
        if (ended)
            return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if (ended)
            return;
        function();
    });
    t.detach();
}

void Timer::setInterval(std::function<void()> function, int interval)
{
    ended = false;
    std::thread t([=]() {
        while (true)
        {
            if (ended)
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if (ended)
                return;
            function();
        }
    });
    t.detach();
}

bool Timer::hasEnded() { return ended; }

void Timer::end()
{
    ended = true;
}
} // namespace Utils