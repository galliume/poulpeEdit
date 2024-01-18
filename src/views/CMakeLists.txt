set(SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/application.h
             ${CMAKE_CURRENT_SOURCE_DIR}/application.c
			 ${CMAKE_CURRENT_SOURCE_DIR}/window.h
             ${CMAKE_CURRENT_SOURCE_DIR}/window.c)

target_sources(PoulpeEdit PRIVATE ${SRC_LIST})