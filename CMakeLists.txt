cmake_minimum_required(VERSION 3.0)
project(OpenGL)

# glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(third/glfw)

# assimp
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(third/assimp)

# bullet
option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(third/bullet)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(Sources/RenderObj/
                    Sources/util/
                    third/Vendor/assimp/include/
                    third/Vendor/bullet/src/
                    third/Vendor/glad/include/
                    third/Vendor/glfw/include/
                    third/Vendor/glm/
                    third/Vendor/stb/)


file(GLOB PROJECT_SOURCES Vendor/glad/src/glad.c
                          Sources/*.cpp
                          Sources/*.hpp
                          Shaders/*.vs
                          Shaders/*.fs)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

# 保留文件目录结构
foreach(source IN LISTS PROJECT_SOURCES)
    file(RELATIVE_PATH source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
    get_filename_component(source_path "${source_rel}" PATH)
    string(REPLACE "/" "\\" source_path_dir "${source_path}")
    source_group("${source_path_dir}" FILES "${source}")
endforeach()

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_CONFIGS})
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)
                      
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

#add_custom_command(
#    TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Glitter/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
#    DEPENDS ${PROJECT_SHADERS})
