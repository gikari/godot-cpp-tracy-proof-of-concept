cmake_minimum_required(VERSION 3.31)

project(profiling_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Ensure the build directory is ignored by Godot
if(NOT EXISTS "${CMAKE_BINARY_DIR}/.gdignore")
    file(WRITE "${CMAKE_BINARY_DIR}/.gdignore" "")
endif()

# Define our GDExtension target library
add_library(${PROJECT_NAME} SHARED
    src/register_types.cpp
    src/register_types.h
    src/profiling_example.cpp
    src/profiling_example.h
)

# Option to enable Tracy profiling
option(EXAMPLE_USE_TRACY "Enable Tracy profiling" OFF)

# Expose the EXAMPLE_EXPORT_TEMPLATE_DIR path option
set(EXAMPLE_EXPORT_TEMPLATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/presets" CACHE PATH "Path to the Godot export template directory")

# Configure godot-cpp FetchContent (always needed)
include(FetchContent)
FetchContent_Declare(
    godot-cpp
    SYSTEM
    GIT_REPOSITORY https://github.com/godotengine/godot-cpp.git
    GIT_TAG        4.5
    GIT_SUBMODULES_RECURSE ON
)

FetchContent_MakeAvailable(godot-cpp)

# Link to godot-cpp target
target_link_libraries(${PROJECT_NAME} PRIVATE godot::cpp)

if(EXAMPLE_USE_TRACY)
    message(STATUS "Tracy profiling is ENABLED")

    # Fetch Tracy headers; implementation lives in Godot's shared tracy.dll
    FetchContent_Declare(
        tracy
        SYSTEM
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG        v0.12.2
        GIT_SHALLOW    TRUE
    )

    FetchContent_MakeAvailable(tracy)

    # Include the public tracy headers
    target_include_directories(${PROJECT_NAME} PRIVATE "${tracy_SOURCE_DIR}/public")

    # Link against Godot's tracy import library (.a = MinGW import lib for tracy.dll)
    find_library(TRACY_LIBRARY
        NAMES tracy libtracy.windows.template_release.x86_64
        PATHS "${EXAMPLE_EXPORT_TEMPLATE_DIR}"
        NO_DEFAULT_PATH
    )

    if(NOT TRACY_LIBRARY)
        message(FATAL_ERROR "Could not find tracy import library in ${EXAMPLE_EXPORT_TEMPLATE_DIR}")
    endif()

    message(STATUS "Using Tracy library: ${TRACY_LIBRARY}")

    # TRACY_IMPORTS: share Godot's tracy.dll instance instead of embedding a second Tracy
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        TRACY_ENABLE TRACY_IMPORTS TRACY_DELAYED_INIT TRACY_MANUAL_LIFETIME)

    target_link_libraries(${PROJECT_NAME} PRIVATE ${TRACY_LIBRARY})
else()
    message(STATUS "Tracy profiling is DISABLED")
endif()

# Output compiled shared library to res://bin/win64/ as profiling_example.dll
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/win64"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/win64"
)
