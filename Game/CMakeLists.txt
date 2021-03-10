project(Game VERSION 0.1.0)

find_package(glad CONFIG REQUIRED)

add_executable(Game "src/main.cpp" "include/main.hpp" "include/tilemap.hpp" "src/tilemap.cpp" "include/camera.hpp" "src/camera.cpp")

target_link_libraries(Game PRIVATE Engine glm)

target_include_directories(Game PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(Game PUBLIC GAME_VERSION="${PROJECT_VERSION}")

add_custom_target(run_game Game)
