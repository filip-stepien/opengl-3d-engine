cmake_minimum_required(VERSION 3.12)
project(opengl-3d-engine)
set(CMAKE_CXX_STANDARD 20)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYFILE_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else(DOXYGEN_FOUND)
    message(STATUS "Doxygen not found, not building docs")
endif(DOXYGEN_FOUND)

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

FetchContent_Declare(
    irrklang
    GIT_REPOSITORY https://github.com/jonas2602/irrKlang.git
    GIT_TAG master
)

FetchContent_GetProperties(irrklang)
if(NOT irrklang_POPULATED)
    FetchContent_Populate(irrklang)
    add_library(irrklang INTERFACE)

    set(IRRKLANG_DLL_PATH ${irrklang_SOURCE_DIR}/bin/winx64-visualStudio)
    set(IRRKLANG_LIB ${irrklang_SOURCE_DIR}/lib/Winx64-visualStudio/irrKlang.lib)

    target_include_directories(irrklang INTERFACE ${irrklang_SOURCE_DIR}/include)
    target_link_libraries(irrklang INTERFACE ${IRRKLANG_LIB})

    file(COPY ${IRRKLANG_DLL_PATH}/irrKlang.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${IRRKLANG_DLL_PATH}/ikpMP3.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY ${IRRKLANG_DLL_PATH}/ikpFlac.dll DESTINATION ${CMAKE_BINARY_DIR})
endif()

add_executable(opengl-3d-engine
    src/Engine.cpp
    src/callbacks.cpp
    src/Shader.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/ElementBuffer.cpp
    src/Texture.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/Light.cpp
    src/Transformable.cpp
    src/EngineObject.cpp
    src/App.cpp
    src/Model.cpp
    src/FrameBuffer.cpp
    src/Plane3D.cpp
    src/Text2D.cpp
    demo/Demo.cpp
    demo/Level.cpp
    demo/Random.cpp
    demo/Enemy.cpp
    demo/SceneManager.cpp
    demo/Gun.cpp
    demo/Scoreboard.cpp
    demo/main.cpp
)

target_link_libraries(opengl-3d-engine PRIVATE glfw glad glm stb_image obj_loader gl_text irrklang)
target_include_directories(opengl-3d-engine PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/demo/include
)

add_dependencies(opengl-3d-engine doc_doxygen)