#ifndef MATH_H
#define MATH_H

#define PI 3.14159265
#define HALF_PI PI / 2

namespace PT        
{
    template <typename T>
    static T map(T map_this, T from_min, T from_max, T to_min, T to_max)
    {
        return (to_max - to_min) * ((map_this - from_min) / (from_max - from_min)) + from_min;
    }
} // namespace PT   


#endif /* MATH_H */
