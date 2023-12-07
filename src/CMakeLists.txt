add_executable(opengl-3d-engine
main.cpp
)

target_link_libraries(opengl-3d-engine PRIVATE glfw glad glm)