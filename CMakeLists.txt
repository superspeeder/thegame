# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenGLEngine")

add_subdirectory("vendor/stb")

find_package(RapidJSON CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_subdirectory("vendor/imgui_backends")

# Include sub-projects.
add_subdirectory("Engine")
add_subdirectory("Game")