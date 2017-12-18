cmake_minimum_required(VERSION 3.0)

project(facade-application)

# Use C++ 14
set(CMAKE_CXX_STANDARD 14)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(ext)

#qt5_wrap_cpp(hello-world_SRC ${CMAKE_CURRENT_SOURCE_DIR}/include/mainwindow.h)

add_executable(facade MACOSX_BUNDLE src/main.cpp src/mainwindow.cpp)

# Add CPR Libraries
target_link_libraries(facade ${CPR_LIBRARIES})

# Include directories 
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})

qt5_use_modules(facade Widgets)

# Use the Widgets module from Qt 5.
#target_link_libraries(facade Qt5::Widgets)

