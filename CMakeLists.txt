cmake_minimum_required(VERSION 3.5)

project(paint LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE main.cpp mainwindow.cpp linegraphscene.cpp redactscene.cpp
    graphicsfigure.cpp ellipsegraphscene.cpp arrowgraphscene.cpp
    zoomgraphsene.cpp pengraphscene.cpp textgraphscene.cpp)
set(HEADER mainwindow.h linegraphscene.h redactscene.h graphicsfigure.h
    ellipsegraphscene.h arrowgraphscene.h zoomgraphsene.h pengraphscene.h)
set(UI mainwindow.ui textgraphscene.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

 add_executable(paint
        ${SOURCE}
        ${HEADER}
        ${UI}
  )

target_link_libraries(paint PRIVATE Qt5::Widgets)
