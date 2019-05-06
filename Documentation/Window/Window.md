# Window

Window handler class.

## WindowConfig

This is a struct which contains the configuration values for the window class.

The current values held are:

| Type         | Name      | Default Value               | Usage                                           |
| ------------ | --------- | --------------------------- | ----------------------------------------------- |
| unsigned int | width     | 800                         | Window width                                    |
| unsigned int | height    | 600                         | Window height                                   |
| bool         | wireframe | false                       | Declares if a primitive is filled or just lines |
| const char\* | title     | "New Window" " Window title |
| int          | major     | 3                           | OpenGL major version                            |
| int          | minor     | 3                           | OpenGL minor version                            |

### Functions

Constructor: `WindowConfig()`
Constructor: `WindowConfig(unsigned int w, unsigned int h, const char* t, int maj, int min)`

## Window

### Configuration & Setup

The window class is instantiated with a constructor that is passed a `WindowConfig` struct.

If nothing is pass then the window will use the default configuration values (See table in 'WindowConfig' section) however you can instantiate with user-defined parameters using: `WindowConfig({800, 300, "User Supplied", 4, 0})`

At any point you are able to reset the configuration to the default values using the `defaultConfig()` function.
