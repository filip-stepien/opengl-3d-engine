cmake_minimum_required(VERSION 3.12)
project(opengl-3d-engine)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(glad)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    gl_text
    GIT_REPOSITORY https://github.com/vallentin/glText.git
    GIT_TAG        master
)

FetchContent_GetProperties(gl_text)
if(NOT gl_text_POPULATED)
    FetchContent_Populate(gl_text)
    add_library(gl_text INTERFACE)
    target_include_directories(gl_text INTERFACE ${gl_text_SOURCE_DIR})
endif()


FetchContent_Declare(
    stb_image
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)

FetchContent_GetProperties(stb_image)
if(NOT stb_image_POPULATED)
    FetchContent_Populate(stb_image)
    add_library(stb_image INTERFACE)
    target_include_directories(stb_image INTERFACE ${stb_image_SOURCE_DIR})
endif()

FetchContent_Declare(
    obj_loader
    GIT_REPOSITORY https://github.com/Bly7/OBJ-Loader.git
    GIT_TAG master
)

if(NOT obj_loader_POPULATED)
    FetchContent_Populate(obj_loader)
    add_library(obj_loader INTERFACE)
    target_include_directories(obj_loader INTERFACE ${obj_loader_SOURCE_DIR}/Source)
endif()

add_executable(opengl-3d-engine
resources/shaders/basic_vertex.glsl
resources/shaders/basic_fragment.glsl
src/main.cpp
src/Engine.cpp
src/Engine.hpp
src/callbacks.cpp
src/callbacks.hpp
src/Shader.cpp
src/Shader.hpp
src/VertexBuffer.cpp
src/VertexBuffer.hpp
src/VertexArray.cpp
src/VertexArray.hpp
src/ElementBuffer.cpp
src/ElementBuffer.hpp
src/Texture.cpp
src/Texture.hpp
src/Camera.cpp
src/Camera.hpp
src/Mesh.cpp
src/Mesh.hpp
src/Light.cpp
src/Light.hpp
src/Transformable.cpp
src/Transformable.hpp
src/Drawable.hpp
src/Updatable.hpp
src/EngineObject.hpp
src/EngineObject.cpp
src/App.cpp
src/App.hpp
src/Model.cpp
src/Model.cpp
src/Model.hpp
src/Model.hpp
src/FrameBuffer.hpp
src/FrameBuffer.cpp
src/Plane3D.hpp
src/Plane3D.cpp
)

target_link_libraries(opengl-3d-engine PRIVATE glfw glad glm stb_image obj_loader gl_text)