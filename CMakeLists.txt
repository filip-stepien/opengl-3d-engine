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
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
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

set(RESOURCES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(RESOURCES_DEST_DIR ${CMAKE_BINARY_DIR}/src)

file(GLOB RESOURCE_FILES LIST_DIRECTORIES true ${RESOURCES_SOURCE_DIR}/*)
file(COPY ${RESOURCE_FILES} DESTINATION ${RESOURCES_DEST_DIR})

add_subdirectory(src)