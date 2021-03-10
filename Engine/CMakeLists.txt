project(Engine VERSION 0.2.0)

add_library(Engine "src/Application.cpp" "include/kat/Application.hpp" "src/Window.cpp" "include/kat/Window.hpp" "include/kat/renderer/Renderer.hpp" "src/Renderer.cpp" "include/kat/renderer/Buffer.hpp" "src/Buffer.cpp" "include/kat/renderer/VertexArray.hpp" "src/VertexArray.cpp" "include/kat/renderer/Shader.hpp" "src/Shader.cpp" "include/kat/Utils.hpp" "src/Utils.cpp" "include/kat/renderer/Texture.hpp" "include/kat/renderer/Tileset.hpp" "src/Texture.cpp" "src/Tileset.cpp" "include/kat/Event.hpp" "src/Event.cpp")

target_link_libraries(Engine PUBLIC glad::glad glfw rapidjson stb glm spdlog::spdlog imgui::imgui imgui_backends)

target_include_directories(Engine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(Engine PUBLIC KAT_ENGINE_VERSION="${PROJECT_VERSION}" -DKAT_DEBUG APPDATA_DIR="${CMAKE_SOURCE_DIR}/KatEngine/")
