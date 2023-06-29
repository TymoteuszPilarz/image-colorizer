cmake_minimum_required(VERSION 3.24)
project(ImageColorization)

set(CMAKE_CXX_STANDARD 23)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_executable(ImageColorization src/main.cpp src/Toolbar.cpp src/Toolbar.h src/Sidebar.cpp src/Sidebar.h src/Content.cpp src/Content.h src/ImagePainter.cpp src/ImagePainter.h src/Canvas.cpp src/Canvas.h)

find_package(Wt REQUIRED)
if(Wt_FOUND)
    message(STATUS "Wt libraries found")
    target_include_directories(ImageColorization PRIVATE ${WT_INCLUDE_DIRS})
    target_link_libraries(ImageColorization PRIVATE ${WT_LIBRARIES})
else()
    message(FATAL_ERROR "Wt libraries not found")
endif()