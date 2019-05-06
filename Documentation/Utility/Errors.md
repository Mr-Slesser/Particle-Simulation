# Errors

## Error types

| Enum        | Constant               | Usage                                 |
| ----------- | ---------------------- | ------------------------------------- |
| Error::TYPE | WINDOW_CREATION_FAIL   | Window creation has failed            |
| Error::TYPE | WINDOW_GLAD_FAIL       | Window failed to initialise GLAD      |
| Error::TYPE | PROGRAM_SHADER_LOAD    | Shader has failed to load into memory |
| Error::TYPE | PROGRAM_SHADER_COMPILE | Shader compilation error              |
| Error::TYPE | PROGRAM_SHADER_LINK    | Shader linking error                  |

## Fatal Errors

Used to flag a fatal error, will terminate execution of the program.

Signature: `void FATALF(t, msg, fn)` / `void FATAL(t, msg)`
Parameters:

-   `t`: `Error::TYPE`: The error type.
-   `msg`: `const char*`: Message to output
-   `fn`: `std::function<void()>`: User specified function to execute upon error.

The functions will output an error message in the format:

> ERROR::TYPE: Message (Line: Filename)
