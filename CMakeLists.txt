project(Engine VERSION 0.1.0)

find_package(RapidJSON CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

set (ENGINE_SOURCES "src/Application.cpp" "include/kat/Application.hpp" "src/Window.cpp" "include/kat/Window.hpp" "include/kat/renderer/Renderer.hpp" "src/Renderer.cpp")

add_library(Engine ${ENGINE_SOURCES} "src/Renderer.cpp")

target_link_libraries(Engine PRIVATE glad::glad glfw rapidjson)
target_link_libraries(Engine PUBLIC glm spdlog::spdlog imgui::imgui)

target_include_directories(Engine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(Engine PUBLIC KAT_ENGINE_VERSION="${PROJECT_VERSION}" -DKAT_DEBUG)
