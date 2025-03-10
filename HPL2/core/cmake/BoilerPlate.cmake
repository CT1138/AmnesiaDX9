### Setup options

# This adds the build directory to the include path automatically
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Unlike APPLE and WIN32, built-in LINUX var was added only in CMake 3.25
if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    set(LINUX ON)
endif()

if(LINUX)
    set(PLATFORM_PREFIX "linux")
    if(CMAKE_SIZEOF_VOID_P MATCHES "8")
        set(CMAKE_EXECUTABLE_SUFFIX ".bin.x86_64")
        set(BIN_RPATH "\$ORIGIN/lib64")
        set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
    else()
        set(CMAKE_EXECUTABLE_SUFFIX ".bin.x86")
        set(BIN_RPATH "\$ORIGIN/lib")
        set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)

        ### Ensure LargeFileSupport on 32-bit linux
        add_compile_definitions(-D_FILE_OFFSET_BITS=64)
    endif()

    set(CMAKE_SKIP_BUILD_RPATH TRUE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH ${BIN_RPATH})
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

elseif(WIN32)
    set(PLATFORM_PREFIX "win32")
    set(CMAKE_EXECUTABLE_SUFFIX ".exe")
    add_compile_definitions(WIN32)  # Frictional's flag used instead of the predefined C++ macro _WIN32

    MESSAGE(WARNING "Windows builds are experimental and will likely produce broken programs.")
else()
    MESSAGE(FATAL_ERROR "Unhandled Platform")
endif()

### Export parent scope
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(STATUS "Exporting variables to parent scope")

    set(LINUX ${LINUX} PARENT_SCOPE)
    set(PLATFORM_PREFIX ${PLATFORM_PREFIX} PARENT_SCOPE)

    set(CMAKE_INCLUDE_CURRENT_DIR ${CMAKE_INCLUDE_CURRENT_DIR} PARENT_SCOPE)
    set(CMAKE_SKIP_BUILD_RPATH ${CMAKE_SKIP_BUILD_RPATH} PARENT_SCOPE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ${CMAKE_BUILD_WITH_INSTALL_RPATH} PARENT_SCOPE)
    set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_RPATH} PARENT_SCOPE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ${CMAKE_INSTALL_RPATH_USE_LINK_PATH} PARENT_SCOPE)
    set(CMAKE_EXECUTABLE_SUFFIX ${CMAKE_EXECUTABLE_SUFFIX} PARENT_SCOPE)
endif()

