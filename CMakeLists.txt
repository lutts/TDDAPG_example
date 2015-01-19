project(CMakeGMockTemplate)
cmake_minimum_required(VERSION 2.8.11)

enable_testing(true)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

include(CommonUtils)

# activate C++ 11
add_definitions(-std=c++11)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# The version number.
set (QTemplate_VERSION_MAJOR 0)
set (QTemplate_VERSION_MINOR 1)
set (QTemplate_VERSION_PATCH 0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)

# find_doxygen()

#add_subdirectory(src)
#add_subdirectory(test)
#add_subdirectory(gtest)
#add_subdirectory(qtest)

set(SRCS QtMovieListEditorView.cpp QtMovieRating.cpp)

set(qt_RESOURCES images.qrc)
qt5_add_resources(qt_GEN_RCS ${qt_RESOURCES})

add_library(nowplaying ${SRCS} ${qt_GEN_RCS})
target_link_libraries(nowplaying Qt5::Widgets)

add_executable(nowplay main.cpp)
target_link_libraries(nowplay nowplaying)

add_subdirectory(tests)

ADD_CPPLINT_SUPPORT("")
