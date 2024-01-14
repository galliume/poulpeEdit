set(SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/socket.h
             ${CMAKE_CURRENT_SOURCE_DIR}/socket_win32.c
			 ${CMAKE_CURRENT_SOURCE_DIR}/socket_linux.c)

target_sources(PoulpeEdit PRIVATE ${SRC_LIST})