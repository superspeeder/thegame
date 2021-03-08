project(stb)

add_library(stb ${PROJECT_SOURCE_DIR}/src/stb_vorbis.c)

target_include_directories(stb PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_compile_definitions(stb PUBLIC -DSTB_IMAGE_IMPLEMENTATION -DSTB_TRUETYPE_IMPLEMENTATION)

add_library(stb::stb ALIAS stb)