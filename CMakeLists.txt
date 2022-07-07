__files_group(${CMAKE_CURRENT_SOURCE_DIR}/enchase/ SRCS)

set(LIBS trimesh2)

__add_real_target(enchase lib SOURCE ${SRCS} 
							  LIB ${LIBS}
							  DEF ${DEFS}
							  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
							  )

if(CC_INSTALL_ENCHASE)
	__install_directory_specif(${CMAKE_CURRENT_SOURCE_DIR} enchase)
endif()