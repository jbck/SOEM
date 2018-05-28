cmake_minimum_required(VERSION 3.1)

project(controller LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

set(SOURCES
    "main.cpp"
    "qml.qrc"
    "slaveinfo.cpp"
    "fal/utils.cpp"
    "fal/object.cpp"
    "fal/subobject.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick soem)
