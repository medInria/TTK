set(TARGET_NAME ITKTensor)

file(GLOB __headers              "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB __templateImplemtation "${CMAKE_CURRENT_SOURCE_DIR}/*.txx")
file(GLOB __templateHeaders      "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

SET(${TARGET_NAME}_HEADERS_ALGORITHMS
    ${__headers}
    ${__templateImplemtation}
    ${__templateHeaders}
    )
    
# Create convertLinearToDF executable
ADD_LIBRARY(                ${TARGET_NAME} ${TTK_BUILD_TYPE})
TARGET_LINK_LIBRARIES(      ${TARGET_NAME} PRIVATE ITKCommon ${TTK_LAPACK_LIBRARIES} )
TARGET_SOURCES(             ${TARGET_NAME} PRIVATE itkNumericTraitsTensorPixel2.cxx itkGradientFileReader.cxx itkGradientFileWriter.cxx)
TARGET_SOURCES(             ${TARGET_NAME} PUBLIC 
                              FILE_SET "publicHeadersITKTensor" 
                              TYPE HEADERS 
                              BASE_DIRS ${CMAKE_SOURCE_DIR}/Common
                              FILES ${${TARGET_NAME}_HEADERS_ALGORITHMS})
                             
TARGET_INCLUDE_DIRECTORIES( ${TARGET_NAME} PUBLIC
                              "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Common;${CMAKE_BINARY_DIR}/Common;${CMAKE_BINARY_DIR}>"
                              "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>include/Common>")

generate_export_header(${TARGET_NAME}
  STATIC_DEFINE ${TARGET_NAME}_BUILT_AS_STATIC
  EXPORT_FILE_NAME "${TARGET_NAME}Export.h"
  )
install(FILES ${PROJECT_BINARY_DIR}/Common/${TARGET_NAME}Export.h DESTINATION include/Common)

SET (FILESET_INSTALL_DIR_publicHeadersITKTensor Common)
                              
export_and_install_libs(${TARGET_NAME})

