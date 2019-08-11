#include "./Core/App.h"

int main(int argc, char const *argv[])
{
    std::stringstream stream;

    stream << "function, "
           << "us, "
           << "ms" << '\n';

    ofstream logfile;
    logfile.open("profile_data.log", ios::app);
    logfile << stream.str();
    logfile.close();

    PT::App app;
    if (app.init())
    {
        app.run();
    }

    return 0;
}