cmake_minimum_required(VERSION 3.19)

project(scrnsv LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(scrnsv main.cpp)

target_sources(scrnsv PRIVATE trayicon.h trayicon.cpp resources.qrc screenshot.h screenshot.cpp overlay.h overlay.cpp)

target_link_libraries(scrnsv PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

target_link_options(scrnsv PRIVATE -mwindows) # NOTE: Без отображения cmd при запуске приложения вне IDE
