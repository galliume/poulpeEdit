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
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

include(gitSubModule)

add_executable(${PROJECT_NAME} src/main.c)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/core)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/network)
  
if(MSVC)
  set(DEBUG_OPTIONS "/WX;/MDd;/std:c17;")
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
if(MSVC)
  list(APPEND GTK_WIN_DLLS
    cairo-2
    cairo-gobject-2
    cairo-script-interpreter-2
    epoxy-0
    ffi-7
    fontconfig-1
    freetype-6
    fribidi-0
    gdk_pixbuf-2.0-0
    gio-2.0-0
    glib-2.0-0
    gmodule-2.0-0
    gobject-2.0-0
    graphene-1.0-0
    gtk-4-1
    harfbuzz
    intl-8
    jpeg-8.2.2
    pango-1.0-0
    pangocairo-1.0-0
    pangowin32-1.0-0
    pcre2-8-0
    pixman-1-0
    png16-16
    tiff4
    z)

  foreach(dll IN LISTS GTK_WIN_DLLS)
    add_custom_command(
      TARGET ${PROJECT_NAME} PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
          ${PROJECT_SOURCE_DIR}/vendor/gtk/bin/${dll}.dll
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/${dll}.dll)
  endforeach()

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

  list(APPEND GTK_LIBS 
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

    target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK_LIBS})

    list(APPEND WIN_LIBS
      Ws2_32
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE ${WIN_LIBS})

	#Filters for visual studio structure
	file(GLOB_RECURSE _source_list "${PROJECT_SOURCE_DIR}/src/**/*.c" "${PROJECT_SOURCE_DIR}/src/**/*.h")
	file(GLOB_RECURSE _source_list "${PROJECT_SOURCE_DIR}/src/*.c" "${PROJECT_SOURCE_DIR}/src/*.h")
	foreach(_source IN ITEMS ${_source_list})
		get_filename_component(_source_path "${_source}" PATH)
		string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
		string(REPLACE "/" "\\" _group_path "${_group_path}")
		source_group("${_group_path}" FILES "${_source}")
	  list(APPEND TIDY_SRC "${_source}")
	endforeach()

	set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
	set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()