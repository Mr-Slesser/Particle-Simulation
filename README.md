# Particle

Particle is a GPU based particle simulation system meant to simulate the movement of particles in a grid of forces, such as wind or water.

<img src="https://raw.githubusercontent.com/ivSlesser/Particle/master/particle.png" alt="Particle Demonstration">

## Technology

-   C++
-   OpenGL (GLEW / Glad)
-   Libraries:

    -   [spdlog](https://github.com/gabime/spdlog)
    -   [ImGui](https://github.com/ocornut/imgui)
    -   [OpenGL Mathematics](https://glm.g-truc.net/0.9.9/index.html)

## Building & Running

### MacOS

Run the script **./Build.sh** in your terminal, which will present a menu with the following supported inputs:

| Input | Function    | Details                                                            |
| ----- | ----------- | ------------------------------------------------------------------ |
| 1     | Build & Run | Generate a gmake project and then builds and runs the application. |
| 2     | Build       | Generate a gmake project and then builds the application.          |
| 3     | Clean       | Removes platform specific project files                            |
| 4     | Generate    | Generates the gmake project files                                  |
| 5     | Commit      | Will prompt for a commit message and then push to the remote repo. |

If this script will not run, you may need to run the following command in your terminal in the Particle root directory: **sudo chmod +x ./Build.sh**

### Windows

Run the script **./Build.bat** in your command prompt, which will present a menu with the following supported inputs:

| Input | Function | Details                                                            |
| ----- | -------- | ------------------------------------------------------------------ |
| 1     | Generate | Generates Visual Studio 2019 project files                         |
| 2     | Clean    | Removes platform specific project files                            |
| 3     | Commit   | Will prompt for a commit message and then push to the remote repo. |
