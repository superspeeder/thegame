project (IMGUIBackends)

add_library(imgui_backends "${PROJECT_SOURCE_DIR}/imgui_impl_glfw.cpp" "${PROJECT_SOURCE_DIR}/imgui_impl_glfw.h" "${PROJECT_SOURCE_DIR}/imgui_impl_opengl3.cpp" "${PROJECT_SOURCE_DIR}/imgui_impl_opengl3.h")

target_include_directories(imgui_backends PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(imgui_backends glad::glad imgui::imgui glfw)

