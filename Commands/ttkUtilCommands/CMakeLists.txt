set(TARGET_NAME ttkUtilCommands)

###############################################
## DEFINE SOURCES FILES
set(${TARGET_NAME}_SRCS
    ${CMAKE_SOURCE_DIR}/Commands/itkDWIBrainMaskExtractorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkDWIBrainMaskExtractorCommandFactory.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkApplyMaskToImageCommand.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkApplyMaskToImageCommandFactory.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToImageCommand.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToImageCommandFactory.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkAddRicianNoiseToImageCommand.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkAddRicianNoiseToImageCommandFactory.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleImageCommand.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleImageCommandFactory.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpImageCommand.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpImageCommandFactory.cxx 
    ${CMAKE_SOURCE_DIR}/Commands/itkAverageStdCalculatorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAverageStdCalculatorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkRBFRotationMatrixExtrapolationCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkRBFRotationMatrixExtrapolationCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkPermute23TensorCoefficientsCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkPermute23TensorCoefficientsCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkSubtractImageCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkSubtractImageCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAverage4DImageCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAverage4DImageCommandFactory.cxx
    )

###############################################
## DEFINE HEADERS FILES
set(${TARGET_NAME}_HEADERS
    ${CMAKE_SOURCE_DIR}/Commands/itkDWIBrainMaskExtractorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDWIBrainMaskExtractorCommandFactory.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkApplyMaskToImageCommand.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkApplyMaskToImageCommandFactory.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToImageCommand.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToImageCommandFactory.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkAddRicianNoiseToImageCommand.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkAddRicianNoiseToImageCommandFactory.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleImageCommand.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleImageCommandFactory.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpImageCommand.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpImageCommandFactory.h 
    ${CMAKE_SOURCE_DIR}/Commands/itkAverageStdCalculatorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAverageStdCalculatorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkRBFRotationMatrixExtrapolationCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkRBFRotationMatrixExtrapolationCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkPermute23TensorCoefficientsCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkPermute23TensorCoefficientsCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkSubtractImageCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkSubtractImageCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAverage4DImageCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAverage4DImageCommandFactory.h
    )

###############################################
## DEFINE DEPENDENCIES
set(LIBRARIES
    ITKProgramFactory
    ITKTensor
	ITKSmoothing
	ITKStatistics
    ${ITKIO_LIBRARIES}
    ${ITK_TRANSFORM_LIBRARIES}
    ${VTK_LIBRARIES}
    ${TTK_LAPACK_LIBRARIES}
	TTK::ttkAlgorithms
  )
    
# Create ttkUtilCommands library
ADD_LIBRARY(                ${TARGET_NAME} ${TTK_BUILD_TYPE})
TARGET_LINK_LIBRARIES(      ${TARGET_NAME} PUBLIC  ${LIBRARIES})
TARGET_SOURCES(             ${TARGET_NAME} PRIVATE ${${TARGET_NAME}_SRCS})
TARGET_SOURCES(             ${TARGET_NAME} PUBLIC 
                              FILE_SET publicHeadersTTKUtilCommands
                              TYPE HEADERS 
                              BASE_DIRS ${CMAKE_SOURCE_DIR}/Commands
                              FILES ${${TARGET_NAME}_HEADERS})
                             
TARGET_INCLUDE_DIRECTORIES( ${TARGET_NAME} PUBLIC
                              "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Commands;${CMAKE_BINARY_DIR}/Commands>"
                              "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/Commands>")

generate_export_header(${TARGET_NAME}
  STATIC_DEFINE ${TARGET_NAME}_BUILT_AS_STATIC
  EXPORT_FILE_NAME "${TARGET_NAME}Export.h"
  )
install(FILES ${PROJECT_BINARY_DIR}/Commands/${TARGET_NAME}/${TARGET_NAME}Export.h DESTINATION include/Commands/${TARGET_NAME})

SET (FILESET_INSTALL_DIR_publicHeadersTTKUtilCommands Commands)
                              
export_and_install_libs(${TARGET_NAME})

