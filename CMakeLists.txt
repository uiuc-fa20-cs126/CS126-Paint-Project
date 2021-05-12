cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(paint)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the working directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Warning flags
if (MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror -Wno-reorder -Wno-import-preprocessor-directive-pedantic -Wno-delete-non-abstract-non-virtual-dtor)
endif ()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if (${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif ()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.x
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if (NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif ()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")
file(GLOB_RECURSE PRETZELGUI_SRC blocks/PretzelGUI/*.cpp)
message(NOTICE ${PRETZELGUI_SRC})
list(APPEND CORE_SOURCE_FILES src/Canvas.cpp src/Toolbar.cpp src/ToolbarButton.cpp src/draw_tools/PaintBrush.cpp src/draw_tools/PaintBucket.cpp src/draw_tools/ShapeTool.cpp src/draw_tools/Eraser.cpp)
list(APPEND SOURCE_FILES ${CORE_SOURCE_FILES} src/PaintApp.cpp)

list(APPEND TEST_FILES tests/TestCanvas.cpp tests/TestPaintBrush.cpp)

ci_make_app(
        APP_NAME paint-app
        CINDER_PATH ${CINDER_PATH}
        SOURCES apps/cinder_app_main.cc ${SOURCE_FILES} ${PRETZELGUI_SRC}
        INCLUDES include blocks/PretzelGUI/src
)

ci_make_app(
        APP_NAME paint-test
        CINDER_PATH ${CINDER_PATH}
        SOURCES ${CORE_SOURCE_FILES} ${TEST_FILES} ${PRETZELGUI_SRC}
        INCLUDES include blocks/PretzelGUI/src
        LIBRARIES catch2
)

if (MSVC)
    set_property(TARGET paint-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif ()