workspace "Particle"
    architecture "x86_64"
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
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/glad/",
        "%{prj.name}/vendor/glfw/"
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