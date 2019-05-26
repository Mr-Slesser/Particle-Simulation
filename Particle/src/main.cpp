#include "./Core/App.h"

#define NK_IMPLEMENTATION
#include "Headers/nuklear.h"

int main(int argc, char const *argv[])
{
    PT::App app;
    if (app.init())
    {
        app.run();
    }

	return 0;
}