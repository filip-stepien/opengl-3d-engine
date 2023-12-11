add_executable(opengl-3d-engine
main.cpp
Engine.cpp
Engine.hpp
callbacks.cpp
callbacks.hpp
Shader.cpp
Shader.hpp
VertexBuffer.cpp
VertexBuffer.hpp
VertexArray.cpp
VertexArray.hpp
ElementBuffer.cpp
ElementBuffer.hpp
)

target_link_libraries(opengl-3d-engine PRIVATE glfw glad glm stb_image)