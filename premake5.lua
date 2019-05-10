workspace "Particle"
    architecture "x64"
    configurations
    {
        "Debug", 
        "Dist",
        "Release"
    }

out = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
gtest = "./vendor/googletest/googletest/"

project "Particle"
    location "Particle"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. out .. "/%{prj.name}")
    objdir ("bin-int/" .. out .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**",
    }

    includedirs
    {
        "vendor/glfw/include",
        "vendor/glad/include"
    }

    libdirs {
        "vendor/glfw/lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        links {
            "glfw3",
            "opengl32"
        }
        defines
        {
            "PT_WIN"
        }

    
    filter "system:macosx"
        cppdialect "C++17"

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
        defines { "PT_DEBUG" }
        symbols "On"

    filter "configurations:Dist"
        defines { "PT_NDEBUG" }
        optimize "On"

    filter "configurations:Release"
        defines { "PT_NDEBUG" }
        optimize "On"

project "GoogleTest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    location "GoogleTest"
    targetdir ("bin/" .. out .. "/%{prj.name}")
    objdir ("bin-int/" .. out .. "/%{prj.name}")

    files {
        (gtest .. "/src/gtest-all.cc")
    }

    includedirs {
        (gtest .. "include"), 
        gtest
    }

project "ParticleTest"
    location "ParticleTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/" .. out .. "/%{prj.name}")
    objdir ("bin-int/" .. out .. "/%{prj.name}")
    
    files {
        "%{prj.name}/src/**",
    }

    includedirs {
        (gtest .. "include"),
        "./Particle/src"
    }

    links { 
        "GoogleTest",
        "Particle"
    }   