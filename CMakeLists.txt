cmake_minimum_required(VERSION 3.21)

project(vk_engine
    VERSION 0.1.0
    LANGUAGES CXX
)

# =====================
# Global settings
# =====================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =====================
# Engine library
# =====================
add_library(engine STATIC
    src/core/windows/window.cpp
    src/graphics/device.cpp
    src/graphics/swapchain.cpp
    src/systems/engine.cpp
    src/systems/renderers/renderer.cpp
)

target_include_directories(engine
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# =====================
# Main executable
# =====================
add_executable(app
    main.cpp
)

target_link_libraries(app
    PRIVATE engine
)

