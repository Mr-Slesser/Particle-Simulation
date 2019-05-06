# Helpers

Utility functions specific to the Graphics area of the application.

## compileShader

Loads a shader from a file and stores the shader ID into a passed value.

`static void compileShader(const char* filePath, int& id)`

Possible to call a fatal error in two places:

-   Shader fails to load: `Error::TYPE::PROGRAM_SHADER_LOAD`
-   Shader fails to compile: `Error::TYPE::PROGRAM_SHADER_COMPILE`
