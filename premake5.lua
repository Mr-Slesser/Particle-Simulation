workspace "Particle"
    configurations
    {
        "Debug32", 
        "Dist32",
        "Release32"
    }

    filter "configurations:*32"
        architecture "x86"

out = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Particle"
    location "Particle"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. out .. "/%{prj.name}")
    objdir ("bin-int/" .. out .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/glad/",
        "/usr/local/include/"
    }

    libdirs {
        "%{prj.name}/vendor/glfw/lib"
    }

    links {
        "glfw"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Dist"
        defines { "NDEBUG" }
        optimize "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"