cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(gtools)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# actual project
add_executable(${PROJECT_NAME}
        src/gtools/gtools.h
        src/gtools/EntryPoint.h
        src/gtools/Application.h src/gtools/Application.cpp
        src/gtools/Layer.h
        src/Example.cpp
        )

include_directories(src/gtools)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
include_directories(lib/glfw/include)

# glad
add_subdirectory(lib/glad)
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glad/include)

# dear imgui
add_subdirectory(lib/imgui-docking)
target_link_libraries(${PROJECT_NAME} imgui-docking)
target_include_directories(${PROJECT_NAME} PUBLIC lib/imgui-docking)

set_target_properties(glad imgui-docking PROPERTIES FOLDER thirdparty)

# setting this project as startup on MSVC
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()