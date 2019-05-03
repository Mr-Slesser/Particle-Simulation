workspace "Particle"
    architecture "x64"
    configurations
    {
        "Debug", 
        "Dist",
        "Release"
    }

out = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
        "%{prj.name}/vendor/glfw/include",
        "%{prj.name}/vendor/glad/include"
    }

    libdirs {
        "%{prj.name}/vendor/glfw/lib"
    }

    links {
        "glfw3",
        "opengl32"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "PT_WIN"
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