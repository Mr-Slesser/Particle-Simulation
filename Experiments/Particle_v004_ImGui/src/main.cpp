#include "./Core/App.h"

int main(int argc, char const *argv[])
{
    PT::App app;
    if (app.init())
    {
        app.run();
    }

	return 0;
}