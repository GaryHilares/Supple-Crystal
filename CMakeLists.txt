# Project settings
cmake_minimum_required(VERSION 3.3.0)
project(Supple-Crystal VERSION 0.1.0)

include(CTest)
enable_testing()

# Build settings
set(CMAKE_BUILD_TYPE "Debug")

# Build process
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(BUILD_TYPES "Debug" "Release" "Tests")
if(NOT ("${CMAKE_BUILD_TYPE}" IN_LIST BUILD_TYPES))
    message(FATAL_ERROR "CMAKE_BUILD_TYPE not recognized: ${CMAKE_BUILD_TYPE} not in ${BUILD_TYPES}")
endif()

set(SFML_DIR "extlibs/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS main graphics window system REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Tests")
    set(GTEST_DIR "extlibs/googletest-1.11.0/")
    set(GTEST_MAIN_LIBRARY "${GTEST_DIR}/lib/libgtest_maind.a")
    set(GTEST_LIBRARY "${GTEST_DIR}/lib/libgtestd.a")
    set(GTEST_INCLUDE_DIR "${GTEST_DIR}/include")
    find_package(GTest REQUIRED)
    set(gtest ${PROJECT_SOURCE_DIR}/${GTEST_LIBRARIES})
else()
    set(gtest "")
    set(GTEST_INCLUDE_DIRS "")
endif()

set(CPPSources
    "src/UI/Controllers/HotkeyController.cpp"
    "src/UI/Controllers/SlideController.cpp"
    "src/UI/Elements/Buttons/PopupMenuButton.cpp"
    "src/UI/Elements/Displays/ImageDisplay.cpp"
    "src/UI/Elements/Menus/ContextMenu.cpp"
    "src/UI/Elements/Menus/PopupMenu.cpp"
    "src/UI/Elements/Menus/ToolbarMenu.cpp"
    "src/Utils/StringOps.cpp"
    "src/Utils/WindowOps.cpp"
    "src/Utils/WindowOpsUnix.cpp"
    "src/Utils/WindowOpsWindows.cpp"
    "src/App.cpp"
    "src/ImageViewer.cpp"
    "src/ResourceLoader.cpp"
    )
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CPPSources ${CPPSources} "src/main.cpp")
    make_directory("${CMAKE_BINARY_DIR}/Release")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release")
    add_executable(Supple-Crystal WIN32 ${CPPSources} resource/icon.rc)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CPPSources ${CPPSources} "src/main.cpp")
    make_directory("${CMAKE_BINARY_DIR}/Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Debug")
    add_executable(Supple-Crystal ${CPPSources} resource/icon.rc)
elseif(CMAKE_BUILD_TYPE STREQUAL "Tests")
    set(CPPSources ${CPPSources})
    make_directory("${CMAKE_BINARY_DIR}/Tests")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tests")
    add_executable(Supple-Crystal ${CPPSources} resource/icon.rc)
endif()
target_include_directories(Supple-Crystal PUBLIC ./extlibs/SFML-2.5.1/include ${GTEST_INCLUDE_DIRS})
target_link_libraries(Supple-Crystal sfml-main sfml-graphics sfml-window sfml-system ${gtest} stdc++fs)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    make_directory("${CMAKE_BINARY_DIR}/Release/assets")
    file(COPY "${PROJECT_SOURCE_DIR}/assets/logo_bg-true_resized.png" DESTINATION "${CMAKE_BINARY_DIR}/Release/assets")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-graphics-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Release")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-window-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Release")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-system-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Release")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    make_directory("${CMAKE_BINARY_DIR}/Debug/assets")
    file(COPY "${PROJECT_SOURCE_DIR}/assets/logo_bg-true_resized.png" DESTINATION "${CMAKE_BINARY_DIR}/Debug/assets")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-graphics-d-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Debug")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-window-d-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Debug")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-system-d-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Tests")
    make_directory("${CMAKE_BINARY_DIR}/Tests/assets")
    file(COPY "${PROJECT_SOURCE_DIR}/assets/logo_bg-true_resized.png" DESTINATION "${CMAKE_BINARY_DIR}/Tests/assets")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-graphics-d-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Tests")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-window-d-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Tests")
    file(COPY "${PROJECT_SOURCE_DIR}/extlibs/SFML-2.5.1/bin/sfml-system-d-2.dll" DESTINATION "${CMAKE_BINARY_DIR}/Tests")
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)