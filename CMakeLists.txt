cmake_minimum_required(VERSION 3.10)
project(GUI_Library)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(COMPILE_COMMANDS "Export compile commands for lsp" OFF)

if(COMPILE_COMMANDS)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  file(CREATE_LINK "${PROJECT_BINARY_DIR}/compile_commands.json"
       "${PROJECT_SOURCE_DIR}/compile_commands.json" SYMBOLIC)
endif()

set(SOURCES
    src/application.cpp
    src/font-manager.cpp
    src/word.cpp
    src/states.cpp
    src/mouse-event.cpp
    src/text-input.cpp
    src/snapshot.cpp
    src/keyboard-shortcuts.cpp
    src/color-manager.cpp
    src/history.cpp)
add_library(GUI_Library ${SOURCES})

add_subdirectory(test)

target_include_directories(GUI_Library PRIVATE include)

target_link_libraries(GUI_Library PUBLIC sfml-graphics sfml-window sfml-system
                                         sfml-audio)

find_package(
  SFML 2.5
  COMPONENTS graphics audio
  REQUIRED)
