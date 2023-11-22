set(TARGET_NAME ttkAlgorithms)

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
TARGET_LINK_LIBRARIES(      ${TARGET_NAME} PRIVATE ITKCommon ${VTK_LIBRARIES} ITKTensor)
TARGET_SOURCES(             ${TARGET_NAME} PRIVATE itkFiberBundleStatisticsCalculator.cxx)
TARGET_SOURCES(             ${TARGET_NAME} PUBLIC 
                              FILE_SET "publicHeadersAlgorithms" 
                              TYPE HEADERS 
                              BASE_DIRS ${CMAKE_SOURCE_DIR}/Algorithms
                              FILES ${${TARGET_NAME}_HEADERS_ALGORITHMS})
                             
TARGET_INCLUDE_DIRECTORIES( ${TARGET_NAME} PUBLIC
                              "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Algorithms;${CMAKE_BINARY_DIR}/Algorithms>"
                              "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>include/Algorithms>")

generate_export_header(${TARGET_NAME}
  STATIC_DEFINE ${TARGET_NAME}_BUILT_AS_STATIC
  EXPORT_FILE_NAME "${TARGET_NAME}Export.h"
  )
install(FILES ${PROJECT_BINARY_DIR}/Algorithms/${TARGET_NAME}Export.h DESTINATION include/Algorithms)

SET (FILESET_INSTALL_DIR_publicHeadersAlgorithms Algorithms)
                              
export_and_install_libs(${TARGET_NAME})

