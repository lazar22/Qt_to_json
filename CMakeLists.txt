cmake_minimum_required(VERSION 3.14)
project(qt_to_json)

set(CMAKE_CXX_STANDARD 17)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(Qt6 COMPONENTS Widgets Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(executable
        main.cpp
        ${LIB_DIR}/window/window.cpp
        ${LIB_DIR}/character/character.cpp
        ${LIB_DIR}/DragImg/dragdropimg.cpp
)

target_include_directories(executable PRIVATE
        ${LIB_DIR}/window
        ${LIB_DIR}/character
        ${LIB_DIR}/DragImg
)

target_link_libraries(executable PRIVATE Qt6::Widgets Qt6::Core)
