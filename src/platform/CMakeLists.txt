set(SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/platform.h
			 ${CMAKE_CURRENT_SOURCE_DIR}/platform_win32.c)

target_sources(PoulpeEdit PRIVATE ${SRC_LIST})