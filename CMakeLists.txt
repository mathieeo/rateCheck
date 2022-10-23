cmake_minimum_required(VERSION 3.14)
project(RateCheck)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

include_directories(${PROJECT_SOURCE_DIR} "support/")


add_library(${PROJECT_NAME} appManager.cpp appManager.h mainwindow.cpp mainwindow.h mainwindow.ui appVersion.h support/benchmark.h support/benchmark.cpp support/start_stop_watch.h support/start_stop_watch.cpp support/file_manager.h support/file_manager.cpp)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
