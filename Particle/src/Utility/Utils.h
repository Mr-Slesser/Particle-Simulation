#ifndef UTILS_HPP
#define UTILS_HPP

namespace Utils
{
    template <typename T>
    static void swap(T* a, T& i, T& j)
    {
        T temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
} // namespace Utils


#endif /* UTILS_HPP */
