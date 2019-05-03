# Premake 5 C++ Project

**Note that currently windows BAT files have not been tested, use with care until this message is removed**

Premake is a build configuration tool for C/C++ in that it generates project files using a LUA configuration.
[Read more about Premake](https://premake.github.io/)

## Features

-   Visual Studio & XCode support
-   Easy build and clean up scripts
-   Easily extensible!

## Building

To build the project there is an included file for both MacOS and Windows, this will generate the project files using the include Premake executable for that platform's build tool.

Windows (VS2017) `Generate.bat`
MacOS (XCode) `./Generate.sh`

If you wish to build for other platforms then you can run Premake directly from the `vendor/bin/<platform>` folder, where `<platform>` is either `win` or `mac`

## Clean Up

The project includes a `.gitignore` file that will filter out the specific project files and outputs, but if you need to manually trigger a clean up then you can use one of two scripts depending on your platform to remove all generated files.

Windows `Clean.bat`
MacOS `Clean.sh`
