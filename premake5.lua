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
        "vendor/glad/include",
        "vendor/glm",
        "vendor/spdlog/include",
        "vendor/imgui"
    }

    libdirs {
        "vendor/glfw/lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        links {
            "glfw3",
            "opengl32",
            "ImGui"
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
        defines { "DEBUG" }
        symbols "On"
        buildoptions {}

    filter "configurations:Dist"
        defines { "NDEBUG" }
        optimize "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "GoogleTest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    location "GoogleTest"

    targetdir ("bin/" .. out .. "/%{prj.name}")
    objdir ("bin-int/" .. out .. "/%{prj.name}")

    files
    {
        (gtest .. "/src/gtest-all.cc")
    }

    includedirs
    {
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
        "./Particle/src",
        "vendor/glfw/include",
        "vendor/glad/include",
        "vendor/glm",
    }

    libdirs {
        "vendor/glfw/lib"
    }

    links { 
        "GoogleTest",
        "Particle"
    }

project "ImGui"
    kind "StaticLib"
    language "C++"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "On"
    location "ImGui"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "vendor/imgui/imconfig.h",
        "vendor/imgui/imgui.h",
        "vendor/imgui/imgui.cpp",
        "vendor/imgui/imgui_draw.cpp",
        "vendor/imgui/imgui_internal.h",
        "vendor/imgui/imgui_widgets.cpp",
        "vendor/imgui/imstb_rectpack.h",
        "vendor/imgui/imstb_textedit.h",
        "vendor/imgui/imstb_truetype.h",
        "vendor/imgui/imgui_demo.cpp"
    }
