set(TARGET_NAME ITKProgramFactory)

###############################################
## DEFINE SOURCES FILES
set(${TARGET_NAME}_SRCS
    ${CMAKE_SOURCE_DIR}/IPF/itkCommandObjectBase.cxx
    ${CMAKE_SOURCE_DIR}/IPF/itkCommandObjectFactory.cxx
    )

###############################################
## DEFINE HEADERS FILES
set(${TARGET_NAME}_HEADERS
    ${CMAKE_SOURCE_DIR}/IPF/itkCommandObjectBase.h
    ${CMAKE_SOURCE_DIR}/IPF/itkCommandObjectFactory.h
    )

###############################################
## DEFINE DEPENDENCIES
set(LIBRARIES
    ITKCommon
    #${ITK_LIBRARIES}
  )
    
# Create ttkCommands library
ADD_LIBRARY(                ${TARGET_NAME} ${TTK_BUILD_TYPE})
TARGET_LINK_LIBRARIES(      ${TARGET_NAME} PUBLIC  ${LIBRARIES})
TARGET_SOURCES(             ${TARGET_NAME} PRIVATE ${${TARGET_NAME}_SRCS})
TARGET_SOURCES(             ${TARGET_NAME} PUBLIC 
                              FILE_SET publicHeadersIPF
                              TYPE HEADERS 
                              BASE_DIRS ${CMAKE_SOURCE_DIR}/IPF
                              FILES ${${TARGET_NAME}_HEADERS})
                             
TARGET_INCLUDE_DIRECTORIES( ${TARGET_NAME} PUBLIC
                              "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/IPF;${CMAKE_BINARY_DIR}/IPF>"
                              "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/IPF>")

generate_export_header(${TARGET_NAME}
  STATIC_DEFINE ITKProgramFactory_BUILT_AS_STATIC
  EXPORT_FILE_NAME "ITKProgramFactoryExport.h"
  )
install(FILES ${PROJECT_BINARY_DIR}/IPF/ITKProgramFactoryExport.h DESTINATION include/IPF)

SET (FILESET_INSTALL_DIR_publicHeadersIPF IPF)

export_and_install_libs(${TARGET_NAME})



###############################################
## TEST PROGRAM
add_executable(programFactoryTest)
TARGET_SOURCES(programFactoryTest PRIVATE
    itkHelloWorldCommand.cxx
    itkHelloWorldCommandFactory.cxx
    programFactoryTest.cxx
    )

target_link_libraries(programFactoryTest
    ITKCommon
    ${TARGET_NAME}
    )

