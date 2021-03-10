project(stb)

add_library(stb ${PROJECT_SOURCE_DIR}/src/stb_vorbis.c ${PROJECT_SOURCE_DIR}/src/stb_image.c)

target_include_directories(stb PUBLIC ${PROJECT_SOURCE_DIR}/include/)

add_library(stb::stb ALIAS stb)