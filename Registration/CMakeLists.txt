SET(TARGET_NAME Registration)

file(GLOB __headers              "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB __templateImplemtation "${CMAKE_CURRENT_SOURCE_DIR}/*.txx")
file(GLOB __templateHeaders      "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

SET(${TARGET_NAME}_HEADERS_REGISTRATION
    ${__headers}
    ${__templateImplemtation}
    ${__templateHeaders}
    )

# Create RPI_INTERFACE interface
ADD_LIBRARY(                ${TARGET_NAME} INTERFACE)                        
TARGET_SOURCES(             ${TARGET_NAME} INTERFACE 
                              FILE_SET "publicHeadersRegistration" 
                              TYPE HEADERS 
                              BASE_DIRS ${CMAKE_SOURCE_DIR}/Registration
                              FILES ${${TARGET_NAME}_HEADERS_COMMON})
TARGET_INCLUDE_DIRECTORIES( ${TARGET_NAME} INTERFACE
                              "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Registration;${CMAKE_BINARY_DIR}/Registration>"
                              "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/Registration>")
                

SET (FILESET_INSTALL_DIR_publicHeadersRegistration Registration)

export_and_install_libs(${TARGET_NAME})

