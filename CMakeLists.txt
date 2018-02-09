cmake_minimum_required(VERSION 3.0)

project(facade-application)

# Use C++ 14
set(CMAKE_CXX_STANDARD 14)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

# Find the Qt5 library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Network REQUIRED)

if (Qt5Widgets_FOUND)
    if (Qt5Widgets_VERSION VERSION_LESS 5.2.0)
        message(FATAL_ERROR "Minimum supported Qt5 version is 5.2!")
    endif()
else()
    message(SEND_ERROR "The Qt5Widgets library could not be found!")
endif(Qt5Widgets_FOUND)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/cpr/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/json/src)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(ext)

# Use custon Windows settings
if (WIN32)
    include_directories(C:/vcpkg/installed/x86-windows/include)
    link_directories(C:/vcpkg/installed/x86-windows/lib)
endif ()

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE RESOURCE_FILES "res/*.icns" "res/*.json" "res/*/*.svg" "res/*/*.jpg" "res/*/*.png" "res/*/*.ttf")

add_executable(facade ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILES})

# Use custom macOS settings
if (APPLE)
    set_target_properties(facade PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/res/Info.plist.in
            MACOSX_BUNDLE TRUE
            MACOSX_FRAMEWORK_IDENTIFIER com.facade.Facade
            RESOURCE "${RESOURCE_FILES}"
    )
endif ()

# Add CPR Libraries
target_link_libraries(facade ${CPR_LIBRARIES})

# Include directories 
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})

qt5_use_modules(facade Widgets Svg)

# Use the Widgets module from Qt 5
target_link_libraries(facade Qt5::Widgets)
target_link_libraries(facade Qt5::Svg)
target_link_libraries(facade Qt5::Network)
