# Particle

Particle is an ongoing project with end product to be a GPU based particle simulation system.

## MacOS

For MacOS the project includes a simple menu driven interface on the command line to handle various aspects of the project, this is in invoked in your terminal with `./Build.sh', with the following supported inputs:

| Input | Function    | Details                                                            |
|-------|-------------|--------------------------------------------------------------------|
| 1     | Build & Run | Generate a gmake project and then builds and runs the application. |
| 2     | Build       | Generate a gmake project and then builds the application.          |
| 3     | Generate    | Generates the project files                                        |
| 4     | Clean       | Removes platform specific project files                            |
| 5     | Commit      | Will prompt for a commit message and then push to the remote repo. |

## Windows

Generate files: `Generate.bat`
Clean files: `Clean.bat`

## GLFW: MacOS

Steps to build GLFW for MacOS:

-   Download and extract the GLFW source code.
-   Open the Terminal.
-   cd to the extracted directory.
-   Type in cmake ., hit return.
-   A Makefile will be created for you.
-   Type in make, hit return.
-   After the compilation process, type in sudo make install.
-   The libraries will be copied to /usr/local/lib/, the header files to /usr/local/include/.
