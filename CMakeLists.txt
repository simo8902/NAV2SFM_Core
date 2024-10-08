cmake_minimum_required(VERSION 3.27)
project(NAV2SFM_Core)

add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")

if(EXISTS "${CMAKE_SOURCE_DIR}/.clang-tidy")
    set(CLANG_TIDY_EXCLUDE_DIRS "external")

else()
    message(STATUS "No .clang-tidy file found, clang-tidy not set.")
endif()

include_directories(
        ${PROJECT_SOURCE_DIR}/src/Engine/Core
        ${PROJECT_SOURCE_DIR}/src/Engine/Rendering
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics
        ${PROJECT_SOURCE_DIR}/src/Engine/SceneManagement
        ${PROJECT_SOURCE_DIR}/src/Engine/Utilities
        ${PROJECT_SOURCE_DIR}/src/Engine/Lighting
)

set(HEADER_FILES
        # Core
        ${PROJECT_SOURCE_DIR}/src/Engine/Core/Initialization.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Core/GameObject.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Core/Component.h

        # Rendering
        ${PROJECT_SOURCE_DIR}/src/Engine/Rendering/Shader.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Rendering/Renderer.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Rendering/Camera.h

        # Physics
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/BoxCollider.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/Capsule.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/CapsuleCollider.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/Collider.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/Cube.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/Cylinder.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/CylinderCollider.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/Ray.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/Sphere.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.h/SphereCollider.h

        # Scene Management
        ${PROJECT_SOURCE_DIR}/src/Engine/SceneManagement/Scene.h
        ${PROJECT_SOURCE_DIR}/src/Engine/SceneManagement/HierarchyManager.h
        ${PROJECT_SOURCE_DIR}/src/Engine/SceneManagement/InspectorManager.h

        # Utilities
        ${PROJECT_SOURCE_DIR}/src/Engine/Utilities/Transform.h
        ${PROJECT_SOURCE_DIR}/src/Engine/Utilities/ProjectExplorer.h

        # Light
        ${PROJECT_SOURCE_DIR}/src/Engine/Lighting/DirectionalLight.h

)

set(SOURCE_FILES
        # Core
        ${PROJECT_SOURCE_DIR}/src/Engine/Core/Initialization.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/Core/GameObject.cpp

        # Rendering
        ${PROJECT_SOURCE_DIR}/src/Engine/Rendering/Shader.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/Rendering/Renderer.cpp

        # Physics
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.cpp/Capsule.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.cpp/Cube.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.cpp/Cylinder.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.cpp/Sphere.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/Physics/.cpp/SphereCollider.cpp

        # Scene Management
        ${PROJECT_SOURCE_DIR}/src/Engine/SceneManagement/Scene.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/SceneManagement/HierarchyManager.cpp
        ${PROJECT_SOURCE_DIR}/src/Engine/SceneManagement/InspectorManager.cpp

        # Utilities
        ${PROJECT_SOURCE_DIR}/src/Engine/Utilities/ProjectExplorer.cpp
)


# GLAD
set(GLAD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/glad/include)
set(GLAD_SOURCE ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c
        src/Engine/Rendering/Material.h
        src/Engine/Rendering/MeshRenderer.h
        src/Engine/Rendering/Mesh.h
        src/Engine/Rendering/Mesh.cpp
        src/Engine/Rendering/MeshFilter.h
        src/Engine/Utilities/AssetManager.h
        src/Engine/Utilities/Logger.h
        src/Engine/Utilities/AssetManager.cpp
        src/Engine/Lighting/DirectionalLight.cpp
        src/Engine/Utilities/SelectionManager.h
        src/Engine/Utilities/SelectionManager.cpp
        src/Engine/Utilities/DragAndDropPayload.h
        src/Engine/Rendering/Material.cpp
        src/Engine/Physics/Texture.cpp
        src/Engine/Physics/Texture.h
)

# ImGuizmo
set(IMGUIzmo_PATH ${CMAKE_SOURCE_DIR}/external/ImGuizmo)

set(BOOST_ROOT "C:/msys64/ucrt64")

find_package(Boost REQUIRED COMPONENTS uuid filesystem system)

if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# IMGUI
set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/external/imgui)

#GLM
set(GLM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/glm/include)

#GLFW
set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/GLFW/include)
set(GLFW_LIBRARIES ${CMAKE_SOURCE_DIR}/external/GLFW/lib/libglfw3.a)

# STB_IMAGE
set(STB_IMAGE_DIR ${CMAKE_SOURCE_DIR}/external/stb_image)

file(GLOB IMGUI_SOURCES
        ${IMGUI_PATH}/*.cpp
        ${IMGUI_PATH}/*.h
        ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
        ${IMGUI_PATH}/backends/imgui_impl_glfw.h
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
        ${IMGUIzmo_PATH}/*.cpp
        ${IMGUIzmo_PATH}/*.h
)

add_library(glad ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)
add_library(ImGui ${IMGUI_SOURCES})

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${IMGUI_PATH})
include_directories(${IMGUIzmo_PATH})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${GLAD_INCLUDE_DIR})
include_directories(${STB_IMAGE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(NAV2SFM_Core main.cpp ${GLAD_SOURCE} ${SOURCE_FILES} ${HEADER_FILES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_USE_UCRT")
endif()

target_compile_options(NAV2SFM_Core PRIVATE -Wno-narrowing)

target_link_libraries(NAV2SFM_Core PRIVATE ${GLFW_LIBRARIES} ${Boost_LIBRARIES} ImGui opengl32 imm32 )