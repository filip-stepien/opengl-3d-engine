add_executable(opengl-3d-engine
main.cpp
Engine.cpp
Engine.hpp
)

target_link_libraries(opengl-3d-engine PRIVATE glfw glad glm)