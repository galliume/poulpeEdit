set(SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/logger.h
             ${CMAKE_CURRENT_SOURCE_DIR}/logger.c
			 ${CMAKE_CURRENT_SOURCE_DIR}/jsmn.c
			 ${CMAKE_CURRENT_SOURCE_DIR}/file.h
             ${CMAKE_CURRENT_SOURCE_DIR}/file.c
			 ${CMAKE_CURRENT_SOURCE_DIR}/engine.h
             ${CMAKE_CURRENT_SOURCE_DIR}/engine.c)

target_sources(PoulpeEdit PRIVATE ${SRC_LIST})