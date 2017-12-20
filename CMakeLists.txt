cmake_minimum_required(VERSION 3.0)

project(facade-application)

# Use C++ 14
set(CMAKE_CXX_STANDARD 14)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(ext)

add_executable(facade MACOSX_BUNDLE src/main.cpp src/mainwindow.cpp src/slack_feedback.cpp)

# Use custom Info.plist file on macOS
if (APPLE)
    set_target_properties(facade PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/res/Info.plist.in)
endif ()

# Add CPR Libraries
target_link_libraries(facade ${CPR_LIBRARIES})

# Include directories 
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})

qt5_use_modules(facade Widgets)

# Use the Widgets module from Qt 5
target_link_libraries(facade Qt5::Widgets)
