cmake_minimum_required(VERSION 3.19)

project(scrnsv LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(scrnsv main.cpp)

qt_add_resources(QRC_FILES resources.qrc)
target_sources(scrnsv PRIVATE ${QRC_FILES})

target_link_libraries(scrnsv PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
