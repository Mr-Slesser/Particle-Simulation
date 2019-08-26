workspace "Particle"
    architecture "x64"
    configurations
    {
        "Debug", 
        "Release"
    }

out = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
gtest = "./vendor/googletest/googletest/"

project "Particle"
    location "Particle"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/" .. out .. "/%{prj.name}")
    objdir ("bin-int/" .. out .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**",
    }
    sysincludedirs { "%{prj.name}/src" }

    includedirs
    {
        "vendor/glfw/include",
        "vendor/glad/include",
        "vendor/glm",
        "vendor/spdlog/include",
    }

    libdirs {
        "vendor/glfw/lib"
    }

    filter "system:windows"
        systemversion "latest"
        
        links {
            "glfw3",
            "opengl32",
        }
        
        defines
        {
            "PT_WIN"
        }

    filter "action:vs*"  -- for Visual Studio actions
        pchheader "PCHeader.h"
        pchsource "%{prj.name}/src/PCHeader.cpp"

    filter "action:not vs*"  -- for everything else
        pchheader "%{prj.name}/src/PCHeader.h"

    
    filter "system:macosx"
        links {
            "glfw3",
            "OpenGL.framework",
            "Cocoa.framework",
            "IOKit.framework",
            "CoreVideo.framework"
        }

        defines
        {
            "PT_MAC"
        }
        linkoptions
        {
            "-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        buildoptions {}

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"