#ifndef GLOBALCONFIGURATION_H
#define GLOBALCONFIGURATION_H

#include <map>

// TODO: Add proper warnings etc.
// TODO: Toggle Bool

namespace PT
{
    class GC
    {
    private:
        static GC* instance;
        GC();

        std::map<const char*, int> ints;
        std::map<const char*, float> floats;
        std::map<const char*, bool> bools;

    public:
        virtual ~GC();
        static GC* get();
        void init();

        int& getInt(const char* name);
        float& getFloat(const char* name);
        bool& getBool(const char* name);

        // TODO: These using '<>' format.
        bool addInt(const char* name, int value);
        bool addFloat(const char* name, float value);
        bool addBool(const char* name, bool value);

        bool updateInt(const char* name, int value);
        bool updateFloat(const char* name, float value);
        bool updateBool(const char* name, bool value);
    };
} // namespace PT

#endif /* GLOBALCONFIGURATION_H */
