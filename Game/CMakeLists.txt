project(Game VERSION 0.1.0)

find_package(glad CONFIG REQUIRED)

set (GAME_SOURCES "src/main.cpp" "include/main.hpp")

add_executable(Game ${GAME_SOURCES})

target_link_libraries(Game PRIVATE Engine)

target_include_directories(Game PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(Game PUBLIC GAME_VERSION="${PROJECT_VERSION}")

add_custom_target(run_game Game)
