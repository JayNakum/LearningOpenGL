workspace "YarnEngine"
    architecture "x64"
    startproject "SandBox"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Yarn2D/vendor/GLFW/include"
IncludeDir["Glad"] = "Yarn2D/vendor/Glad/include"
IncludeDir["imGui"] = "Yarn2D/vendor/imgui"

-- include "Yarn2D/vendor/GLFW"
-- include "Yarn2D/vendor/Glad"
-- include "Yarn2D/vendor/imgui"

group "Dependencies"
	include "Yarn2D/vendor/GLFW"
	include "Yarn2D/vendor/Glad"
	include "Yarn2D/vendor/imgui"

group ""

project "Yarn2D"
    location "Yarn2D"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "YarnPCH.h"
    pchsource "%{prj.name}/src/YarnPCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        -- staticruntime "On"
        systemversion "latest"

        defines
        {
            "YARN_PLATFORM_WINDOWS",
            "YARN_BUILD_DLL",
            -- "_WINDLL"
            -- "_UNICODE"
            -- "UNICODE"
            "GLFW_INCLUDE_NONE"
        }
        
        postbuildcommands
        {
            -- ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }
    
    filter "configurations:Debug"
        defines "YARN_DEBUG"
        -- buildoptions "/MDd"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "YARN_RELEASE"
        -- buildoptions "/MD"
        runtime "Release"
        optimize "On"

    filter "configurations:Distribution"
        defines "YARN_DISTRIBUTION"
        runtime "Release"
        optimize "On"

    -- filter {"system:windows", "configurations:Release"}
    --     buildoptions "/MT"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs
    {
        "Yarn2D/src",
        "Yarn2D/vendor/spdlog/include"
    }

    links
    {
        "Yarn2D"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        -- staticruntime "On"
        systemversion "latest"
        
        defines
        {
            "YARN_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "YARN_DEBUG"
        -- buildoptions "/MDd"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "YARN_RELEASE"
        -- buildoptions "/MD"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Distribution"
        defines "YARN_DISTRIBUTION"
        -- buildoptions "/MD"
        runtime "Release"
        optimize "On"
    
    -- filter {"system:windows", "configurations:Release"}
    --     buildoptions "/MT"