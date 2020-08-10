# Particle Simulation

This project a GPU based particle simulation system meant to simulate the movement of particles in a grid of forces, such as wind or water. This implementation uses Perlin noise to generate the noise field with which the particles interact.

This project serves as a prototype for a BSc Computer Science Dissertation project, discarded in favor of another topic the actual implementation is complete and able to be used.

<img width="500" src="https://raw.githubusercontent.com/ivSlesser/Particle/master/particle.png" alt="Particle Demonstration"><br/>

This project uses GLFW and OpenGL to handle windowing and GPU commands.

## Building & Running

This project is only currently officially supported on MacOS devices.

Run the script **./Build.sh** in your terminal, which will present a menu with the following supported inputs:

| Input | Function    | Details                                                            |
| ----- | ----------- | ------------------------------------------------------------------ |
| 1     | Build & Run | Generate a gmake project and then builds and runs the application. |
| 2     | Build       | Generate a gmake project and then builds the application.          |
| 3     | Clean       | Removes platform specific project files                            |
| 4     | Generate    | Generates the gmake project files                                  |
| 5     | Commit      | Will prompt for a commit message and then push to the remote repo. |

If this script will not run, you may need to run the following command in your terminal in the Particle root directory: **sudo chmod +x ./Build.sh**
