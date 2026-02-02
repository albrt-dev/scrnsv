cmake_minimum_required(VERSION 3.19)

project(scrnsv LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(scrnsv main.cpp)

target_sources(scrnsv PRIVATE screenshot.h screenshot.cpp trayicon.h trayicon.cpp resources.qrc)

target_link_libraries(scrnsv PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
