#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

namespace Exception
{
class Example : public std::exception
{
    const char *msg;

public:
    Example(const char *msg)
        : msg(msg) {}

    const char *what()
    {
        return msg;
    }
};
} // namespace Exception

#endif /* EXCEPTION_HPP */
