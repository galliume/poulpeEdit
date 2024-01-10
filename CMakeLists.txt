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
  set(DEBUG_OPTIONS "/WX;/MDd;/MDd;/std:c17;")
  set(RELEASE_OPTIONS "-O2;/Obd2;/Ot;/MD;/fp:fast")
else()
  set(DEBUG_OPTIONS "-Wextra;-Wall;-Werror;-Wshadow;-Wfloat-equal;-Wundef;-Wpointer-arith;-Wcast-align;-Wstrict-prototypes;-Wstrict-overflow=1;-Wwrite-strings;-Waggregate-return;-Wcast-qual;-Wswitch-default;-Wswitch-enum;-Wconversion;-Wunreachable-code")
  set(RELEASE_OPTIONS "-O2")
endif()

target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
#########################################################

#########################################################7
##################### External libs #####################
#########################################################
include_directories(
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/cairo
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/epoxy
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/fontconfig
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/freetype2
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/fribidi
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/gdk-pixbuf-2.0
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/gio-win32-2.0
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/glib-2.0
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/graphene-1.0
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/gtk-4.0
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/harfbuzz
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/libpng16
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/pango-1.0
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/pixman-1
  ${PROJECT_SOURCE_DIR}/vendor/gtk/include/sass
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/glib-2.0/include
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/graphene-1.0/include)

list(APPEND EXTRA_LIBS 
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/cairo.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/epoxy.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/ffi.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/fontconfig.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/freetype.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/fribidi.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/gdk_pixbuf-2.0.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/gio-2.0.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/glib-2.0.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/gmodule-2.0.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/gobject-2.0.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/graphene-1.0.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/gtk-4.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/harfbuzz.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/intl.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/png16.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/pango-1.0.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/pixman-1.lib
  ${PROJECT_SOURCE_DIR}/vendor/gtk/lib/sass.lib)

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTRA_LIBS})

add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/gobject-2.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/gobject-2.0-0.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/gtk-4-1.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/gtk-4-1.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/gio-2.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/gio-2.0-0.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/ffi-7.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/ffi-7.dll)

 add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/glib-2.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/glib-2.0-0.dll)  

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/intl-8.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/intl-8.dll)  

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/z.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/z.dll)  

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/gmodule-2.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/gmodule-2.0-0.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/pcre2-8-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/pcre2-8-0.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/pangocairo-1.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/pangocairo-1.0-0.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/fribidi-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/fribidi-0.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/harfbuzz.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/harfbuzz.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/cairo-2.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/cairo-2.dll)    

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/png16-16.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/png16-16.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/pango-1.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/pango-1.0-0.dll)     

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/cairo-gobject-2.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/cairo-gobject-2.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/epoxy-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/epoxy-0.dll) 

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/gdk_pixbuf-2.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/gdk_pixbuf-2.0-0.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/graphene-1.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/graphene-1.0-0.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/pangowin32-1.0-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/pangowin32-1.0-0.dll)                 

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/tiff4.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/tiff4.dll) 

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/jpeg-8.2.2.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/jpeg-8.2.2.dll)

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/cairo-script-interpreter-2.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/cairo-script-interpreter-2.dll) 

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/freetype-6.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/freetype-6.dll)       

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/fontconfig-1.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/fontconfig-1.dll)           

  add_custom_command(
  TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/pixman-1-0.dll
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/pixman-1-0.dll)       