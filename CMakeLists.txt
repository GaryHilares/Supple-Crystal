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

set(SFML_ROOT_DIR "extlibs/SFML-2.5.1")
set(SFML_DIR "${SFML_ROOT_DIR}/lib/cmake/SFML")
find_package(SFML COMPONENTS main graphics window system REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Tests")
    set(GTEST_ROOT_DIR "extlibs/googletest-1.11.0/")
    set(GTEST_MAIN_LIBRARY "${GTEST_ROOT_DIR}/lib/libgtest_maind.a")
    set(GTEST_LIBRARY "${GTEST_ROOT_DIR}/lib/libgtestd.a")
    set(GTEST_INCLUDE_DIR "${GTEST_ROOT_DIR}/include")
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
    "src/MessageBox.cpp"
    )

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Release")
set(CPPSources ${CPPSources} src/main.cpp)
elseif(CMAKE_BUILD_TYPE STREQUAL "Tests")
    set(CPPSources ${CPPSources} tests/tests.cpp)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
make_directory("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CPPSources ${CPPSources} "src/main.cpp")
    add_executable(Supple-Crystal WIN32 ${CPPSources} resource/icon.rc)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CPPSources ${CPPSources} "src/main.cpp")
    add_executable(Supple-Crystal ${CPPSources} resource/icon.rc)
elseif(CMAKE_BUILD_TYPE STREQUAL "Tests")
    set(CPPSources ${CPPSources})
    add_executable(Supple-Crystal ${CPPSources} resource/icon.rc)
endif()

set(LINK_LIBRARIES sfml-main sfml-graphics sfml-window sfml-system stdc++fs)
set(INCLUDE_DIRS ${SFML_ROOT_DIR}/include)
if(CMAKE_BUILD_TYPE STREQUAL "Tests")
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
    set(LINK_LIBRARIES ${LINK_LIBRARIES} ${gtest})
endif()
target_include_directories(Supple-Crystal PRIVATE ${INCLUDE_DIRS})
target_link_libraries(Supple-Crystal ${LINK_LIBRARIES})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(SFML_DLL_FILENAMES "sfml-graphics-2.dll" "sfml-system-2.dll" "sfml-window-2.dll")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Tests")
    set(SFML_DLL_FILENAMES "sfml-graphics-d-2.dll" "sfml-system-d-2.dll" "sfml-window-d-2.dll")
endif()

foreach(FILENAME ${SFML_DLL_FILENAMES})
    file(COPY "${SFML_ROOT_DIR}/bin/${FILENAME}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endforeach()

make_directory("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
file(COPY "${PROJECT_SOURCE_DIR}/assets/logo_bg-true_resized.png" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")

if(CMAKE_BUILD_TYPE STREQUAL "Tests")
    gtest_discover_tests(Supple-Crystal)
    add_custom_command(
        TARGET Supple-Crystal
        POST_BUILD
        COMMAND "ctest.exe" "--output-on-failure"
    )
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)