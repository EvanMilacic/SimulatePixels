cmake_minimum_required(VERSION 3.13)
project(SimulatePixels CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/TestScreenOutput)

# Simulation core + SDL platform layer. win32_platform.cpp is intentionally
# excluded: it is a separate, Visual-Studio-only entry point for anyone who
# wants a pure Win32/GDI build instead of the cross-platform SDL2 one.
file(GLOB CORE_SOURCES ${SRC_DIR}/*.cpp)
list(REMOVE_ITEM CORE_SOURCES ${SRC_DIR}/win32_platform.cpp)

add_executable(SimulatePixels ${CORE_SOURCES})
target_include_directories(SimulatePixels PRIVATE ${SRC_DIR})

if(NOT EMSCRIPTEN)
    # Emscripten's OpenMP implementation needs -pthread wired through the whole
    # build (worker threads, SharedArrayBuffer, COOP/COEP headers, etc.), which
    # this project isn't set up for. Skip it for the browser build; the
    # "#pragma omp parallel for" in MT_sd_Controller.cpp is simply ignored by
    # the compiler and the simulation runs single-threaded there instead.
    find_package(OpenMP)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(SimulatePixels PRIVATE OpenMP::OpenMP_CXX)
    endif()
endif()

if(EMSCRIPTEN)
    # Emscripten ships its own SDL2 port; no system package needed.
    target_compile_options(SimulatePixels PRIVATE -sUSE_SDL=2)
    target_link_options(SimulatePixels PRIVATE -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1)
    set_target_properties(SimulatePixels PROPERTIES SUFFIX ".html")
else()
    find_package(SDL2 REQUIRED)
    target_include_directories(SimulatePixels PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(SimulatePixels PRIVATE ${SDL2_LIBRARIES})
endif()
