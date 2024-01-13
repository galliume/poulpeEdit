set(SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/socket.h
             ${CMAKE_CURRENT_SOURCE_DIR}/winSocket.c)

target_sources(PoulpeEdit PRIVATE ${SRC_LIST})