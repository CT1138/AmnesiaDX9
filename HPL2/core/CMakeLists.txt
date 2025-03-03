cmake_minimum_required (VERSION 3.19)
project(HPL2)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(BoilerPlate)

# Set up dependency directories (CACHE = global scope)
set(DEPENDENCIES_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/precompiled CACHE PATH "Dir which holds precompiled dependencies - libs and headers")
if(MINGW)
    set(DEPENDENCIES_PLATFORM_LIBS "${DEPENDENCIES_ROOT}/lib/mingw32;${DEPENDENCIES_ROOT}/lib/win32" CACHE PATH "Dir which holds prebuilt libraries for target system")
else()
    set(DEPENDENCIES_PLATFORM_LIBS ${DEPENDENCIES_ROOT}/lib/${PLATFORM_PREFIX} CACHE PATH "Dir which holds prebuilt libraries for target system")
endif()

# Specify the static linking options for GCC and C++ runtimes
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

include(UtilityFunctions)

add_subdirectory(../../dependencies/OALWrapper build_oalwrapper)

# We use SDL2 by default in CMake now, but SDL 1.2 is also supported in the code. We need to instruct it to use SDL2.
add_compile_definitions(USE_SDL2 USE_OALWRAPPER)

# Common shared source
file(GLOB common_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    sources/ai/*
    sources/engine/*
    sources/generate/*
    sources/graphics/*
    sources/gui/*
    sources/haptic/*
    sources/input/*
    sources/math/*
    sources/physics/*
    sources/resources/*
    sources/scene/*
    sources/sound/*
	sources/system/*
	sources/*.*

    include/ai/*
    include/engine/*
    include/generate/*
    include/graphics/*
    include/gui/*
    include/haptic/*
    include/input/*
    include/math/*
    include/physics/*
    include/resources/*
    include/scene/*
    include/sound/*
    include/system/*
    include/*.*
)
list(REMOVE_DUPLICATES common_sources)

# Implementation unfinished
if(NOT COLORGRADING_SUPPORT)
    list(REMOVE_ITEM common_sources
        sources/graphics/PostEffect_ColorGrading.cpp
        include/graphics/PostEffect_ColorGrading.h
    )
endif()

# Setup various implementation sources
file(GLOB impl_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    include/impl/tinyXML/*
    include/impl/*.*

    # TinyXML
    sources/impl/tinyXml/*
    sources/impl/XmlDocumentTiny.cpp
    # Scripting
    sources/impl/SqScript.cpp
    sources/impl/scriptarray.cpp
    sources/impl/scripthelper.cpp
    sources/impl/scriptstring.cpp
    sources/impl/scriptstring_utils.cpp
    # Image Loading
    sources/impl/BitmapLoader*
    # Theora Video
    sources/impl/VideoStreamTheora.cpp
    # Newton
    sources/impl/*Newton.cpp
    # GL
    sources/impl/FrameBufferGL.cpp
    sources/impl/GLSL*
    sources/impl/OcclusionQueryOGL.cpp
    sources/impl/VertexBufferOGL_Array.cpp
    sources/impl/VertexBufferOGL_VBO.cpp
    sources/impl/VertexBufferOpenGL.cpp
    # SDL
    sources/impl/GamepadSDL.cpp
    sources/impl/GamepadSDL2.cpp
    sources/impl/KeyboardSDL.cpp
    sources/impl/MouseSDL.cpp
    sources/impl/MutexSDL.cpp
    sources/impl/ThreadSDL.cpp
    sources/impl/TimerSDL.cpp
    sources/impl/LowLevelGraphicsSDL.cpp
    sources/impl/LowLevelInputSDL.cpp
    sources/impl/LowLevelResourcesSDL.cpp
    sources/impl/LowLevelSystemSDL.cpp
    sources/impl/SDLEngineSetup.cpp
    sources/impl/SDLFontData.cpp
    sources/impl/SDLTexture.cpp
    # OpenAL
    sources/impl/LowLevelSoundOpenAL.cpp
    sources/impl/OpenAL*
    # Mesh Loader
    sources/impl/MeshLoaderCollada.cpp
    sources/impl/MeshLoaderColladaHelpers.cpp
    sources/impl/MeshLoaderColladaLoader.cpp
    sources/impl/MeshLoaderMSH.cpp
)

if(LINUX)
    LIST(APPEND impl_sources
        sources/impl/PlatformUnix.cpp
        sources/impl/PlatformSDL.cpp
    )
elseif(WIN32)
    LIST(APPEND impl_sources
        sources/impl/MutexWin32.cpp
        sources/impl/ThreadWin32.cpp
        sources/impl/PlatformWin32.cpp
    )
endif()

if(FBX_SUPPORT)
    list(APPEND impl_sources
        sources/impl/MeshLoaderFBX.cpp
    )
endif()

# Setup source groups
source_group("AI" REGULAR_EXPRESSION "\\/ai\\/.+")
source_group("Engine" REGULAR_EXPRESSION "\\/engine\\/.+")
source_group("Generate" REGULAR_EXPRESSION "\\/generate\\/.+")
source_group("Graphics" REGULAR_EXPRESSION "\\/graphics\\/.+")
source_group("GUI" REGULAR_EXPRESSION "\\/gui\\/.+")
source_group("Input" REGULAR_EXPRESSION "\\/input\\/.+")
source_group("Math" REGULAR_EXPRESSION "\\/math\\/.+")
source_group("Physics" REGULAR_EXPRESSION "\\/physics\\/.+")
source_group("Resources" REGULAR_EXPRESSION "\\/resources\\/.+")
source_group("Scene" REGULAR_EXPRESSION "\\/scene\\/.+")
source_group("Sound" REGULAR_EXPRESSION "\\/sound\\/.+")
source_group("System" REGULAR_EXPRESSION "\\/system\\/.+")

source_group("Implementation Specific" REGULAR_EXPRESSION "\\/impl\\/.+")
source_group("TinyXML" REGULAR_EXPRESSION "\\/impl\\/tiny.+")
source_group("SDL Specific" REGULAR_EXPRESSION "\\/impl\\/.*SDL.+")
source_group("OpenGL Specific" REGULAR_EXPRESSION "\\/impl\\/.*GL.+")
source_group("HaptX Specific" REGULAR_EXPRESSION "\\/impl\\/.+HaptX.+")
source_group("Newton Specific" REGULAR_EXPRESSION "\\/impl\\/.+Newton.+")
source_group("Mesh Loaders" REGULAR_EXPRESSION "\\/impl\\/Mesh.+")
source_group("OpenAL Specific" REGULAR_EXPRESSION "\\/impl\\/.*OpenAL.+")
source_group("Win32" REGULAR_EXPRESSION "\\/impl\\/.+Win32.+")
source_group("Platform" REGULAR_EXPRESSION "\\/impl\\/Platform.+")

# Setup HPL2 compile target

add_library(HPL2 STATIC ${common_sources} ${impl_sources})

set(HPL2_INCLUDES
    PUBLIC include
    # Ensure this is listed before dependencies to use the correct OpenAL headers
    PRIVATE ${OALWRAPPER_INCLUDE_DIR}
    PRIVATE ../../dependencies/AngelScript/include
    PUBLIC ${DEPENDENCIES_ROOT}/include
)

if(LINUX)
    add_library(binreloc STATIC ../../dependencies/binreloc/binreloc.c)
    set_target_properties(binreloc PROPERTIES COMPILE_DEFINITIONS "ENABLE_BINRELOC")

    list(APPEND HPL2_INCLUDES
        ../../dependencies/binreloc/
    )
endif()

target_include_directories(HPL2 ${HPL2_INCLUDES})

# Setup libs

if(MINGW)
    FindPrebuiltLibrary(NEWTON_LIBRARY newton)
    FindPrebuiltLibrary(FBX_LIBRARY fbxsdk-2012.2-md)
    FindPrebuiltLibrary(GLEW_LIBRARY glew32)
    FindPrebuiltLibrary(DEVIL_LIBRARY DevIL)

    add_subdirectory(../../dependencies/AngelScript build_angelscript)
    target_link_libraries(HPL2 angelscript)
elseif(WIN32)
    FindPrebuiltLibrary(NEWTON_LIBRARY newton)
    FindPrebuiltLibrary(FBX_LIBRARY fbxsdk-2012.2-md)
    FindPrebuiltLibrary(GLEW_LIBRARY glew32)
    FindPrebuiltLibrary(DEVIL_LIBRARY DevIL)

    FindPrebuiltLibrary(ANGELSCRIPT_LIBRARY angelscript)
    target_link_libraries(HPL2 ${ANGELSCRIPT_LIBRARY})
else()
    FindPrebuiltLibrary(NEWTON_LIBRARY Newton)
    FindPrebuiltLibrary(FBX_LIBRARY fbxsdk-2012.2-static)
    FindPrebuiltLibrary(GLEW_LIBRARY GLEW)
    FindPrebuiltLibrary(DEVIL_LIBRARY IL)

    FindPrebuiltLibrary(ANGELSCRIPT_LIBRARY angelscript)
    target_link_libraries(HPL2 ${ANGELSCRIPT_LIBRARY})
endif()

FindPrebuiltLibrary(THEORA_LIBRARY theora)
FindPrebuiltLibrary(DEVIL_LIBRARY IL)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL)

if(LINUX)
    set(PLATFORM_LIBS
        binreloc
        pthread
        dl
    )
endif()

target_link_libraries(HPL2
    OALWrapper # Links OGG, Vorbis, and SDL
    ${NEWTON_LIBRARY}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLEW_LIBRARY}
    ${THEORA_LIBRARY}
    ${DEVIL_LIBRARY}
    ${PLATFORM_LIBS}
)

if(FBX_SUPPORT)
    target_link_libraries(HPL2 ${FBX_LIBRARY})
endif()

if(MINGW)
    add_subdirectory(../../dependencies/zlib build_zlib)
    target_link_libraries(HPL2 zlib)
    find_path(ZCONF_DIR zconf.h PATHS ${CMAKE_CURRENT_BINARY_DIR}/build_zlib REQUIRED NO_DEFAULT_PATH)
    message(STATUS "zconfdir ${ZCONF_DIR}")
    target_include_directories(HPL2
        PRIVATE ../../dependencies/zlib
        PRIVATE ${ZCONF_DIR}
    )
elseif(WIN32)
    FindPrebuiltLibrary(ZLIB zlib)
    target_link_libraries(HPL2 ${ZLIB})
else()
    # Use system ZLIB
    find_package(ZLIB REQUIRED)
    target_link_libraries(HPL2 ${ZLIB_LIBRARIES})
    target_include_directories(HPL2 PRIVATE ${ZLIB_INCLUDE_DIRS})
endif()

message(STATUS
    "Core libs:
    ${ZLIB_LIBRARIES}
    ${NEWTON_LIBRARY}
    ${ANGELSCRIPT_LIBRARY}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
    ${GLEW_LIBRARY}
    ${THEORA_LIBRARY}
    ${DEVIL_LIBRARY}
    ${FBX_LIBRARY}
    ${PLATFORM_LIBS}"
)

add_subdirectory(../tools build_tools)

