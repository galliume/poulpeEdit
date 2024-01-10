#########################################################
##################### PoulpeEdit Project ################
#########################################################
cmake_minimum_required(VERSION 3.25.2)

project(PoulpeEdit
  VERSION 0.1.1
  DESCRIPTION "Level editor for PoulpeEngine"
  HOMEPAGE_URL "https://github.com/galliume/poulpeEdit"
  LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

include(gitSubModule)

add_executable(${PROJECT_NAME} src/main.c)

include_directories(${PROJECT_SOURCE_DIR}/src)

if(MSVC)
  set(DEBUG_OPTIONS "/WX;/MDd;/Wall;/MDd;/std:c17;")
  set(RELEASE_OPTIONS "-O2;/Obd2;/Ot;/MD;/fp:fast")
else()
  set(DEBUG_OPTIONS "-Wextra;-Wall;-Werror;-Wshadow;-Wfloat-equal;-Wundef;-Wpointer-arith;-Wcast-align;-Wstrict-prototypes;-Wstrict-overflow=1;-Wwrite-strings;-Waggregate-return;-Wcast-qual;-Wswitch-default;-Wswitch-enum;-Wconversion;-Wunreachable-code")
  set(RELEASE_OPTIONS "-O2")
endif()

target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
#########################################################

#########################################################
##################### External libs #####################
#########################################################
include_directories(${PROJECT_SOURCE_DIR}/vendor/gtk/include/gtk)

list(APPEND EXTRA_LIBS ${PROJECT_SOURCE_DIR}/gtk-4.lib)

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTRA_LIBS})
