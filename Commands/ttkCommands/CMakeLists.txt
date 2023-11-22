set(TARGET_NAME ttkCommands)

###############################################
## DEFINE SOURCES FILES
set(${TARGET_NAME}_SRCS
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpTensorImageCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpTensorImageCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkNPTRemoverCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkNPTRemoverCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorFlipCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorFlipCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToTensorsCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToTensorsCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIEstimatorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIEstimatorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIMultiEstimatorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIMultiEstimatorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToDWICommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToDWICommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkFiberTrackingCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkFiberTrackingCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkSheetTrackingCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkSheetTrackingCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIEstimatorWithBFGSCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIEstimatorWithBFGSCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkLogEuclideanDTIEstimatorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkLogEuclideanDTIEstimatorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorZScoreCalculatorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorZScoreCalculatorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorAnisotropicFilteringCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorAnisotropicFilteringCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkNormalizeTensorsCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkNormalizeTensorsCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorGaussianFilteringCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorGaussianFilteringCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkSparseTensorsExtrapolationCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkSparseTensorsExtrapolationCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkRBFTensorExtrapolationCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkRBFTensorExtrapolationCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorNormalizedGaussianInterpolationCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorNormalizedGaussianInterpolationCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpFibersCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpFibersCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkHessianTensorImageCalculatorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkHessianTensorImageCalculatorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleTensorImageCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleTensorImageCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleTensorImage2Command.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleTensorImage2CommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorToScalarCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorToScalarCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorsToDWICommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorsToDWICommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkSyntheticTensorFieldGeneratorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkSyntheticTensorFieldGeneratorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkBoostTensorAnisotropyCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkBoostTensorAnisotropyCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAverageStdTensorCalculatorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkAverageStdTensorCalculatorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorGradientMagnitudeCalculatorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorGradientMagnitudeCalculatorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkNormalize2TensorsCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkNormalize2TensorsCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkScaleTensorCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkScaleTensorCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkComputeBundleStatisticsCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkComputeBundleStatisticsCommandFactory.cxx
    )

if (TTK_USE_GMM)
    set(TTK_COMMAND_SRCS
        ${TTK_COMMAND_SRCS}
        ${CMAKE_SOURCE_DIR}/Commands/itkDemonsTensorRegistrationCommand.cxx
        ${CMAKE_SOURCE_DIR}/Commands/itkDemonsTensorRegistrationCommandFactory.cxx
        ${CMAKE_SOURCE_DIR}/Commands/itkLogDomainDemonsTensorRegistrationCommand.cxx
        ${CMAKE_SOURCE_DIR}/Commands/itkLogDomainDemonsTensorRegistrationCommandFactory.cxx
        )
endif (TTK_USE_GMM)

if (TTK_USE_VTKINRIA3D)
    set(TTK_COMMAND_SRCS
        ${TTK_COMMAND_SRCS}
        ${CMAKE_SOURCE_DIR}/Commands/itkExtractBundleWithROICommand.cxx
        ${CMAKE_SOURCE_DIR}/Commands/itkExtractBundleWithROICommandFactory.cxx
        )
endif (TTK_USE_VTKINRIA3D)

###############################################
## DEFINE HEADERS FILES
set(${TARGET_NAME}_HEADERS
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpTensorImageCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpTensorImageCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkNPTRemoverCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkNPTRemoverCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorFlipCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorFlipCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToTensorsCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToTensorsCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIEstimatorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIEstimatorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIMultiEstimatorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIMultiEstimatorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToDWICommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAddGaussianNoiseToDWICommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkFiberTrackingCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkFiberTrackingCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkSheetTrackingCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkSheetTrackingCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIEstimatorWithBFGSCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDTIEstimatorWithBFGSCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkLogEuclideanDTIEstimatorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkLogEuclideanDTIEstimatorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorZScoreCalculatorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorZScoreCalculatorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorAnisotropicFilteringCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorAnisotropicFilteringCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkNormalizeTensorsCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkNormalizeTensorsCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorGaussianFilteringCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorGaussianFilteringCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkSparseTensorsExtrapolationCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkSparseTensorsExtrapolationCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkRBFTensorExtrapolationCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkRBFTensorExtrapolationCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorNormalizedGaussianInterpolationCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorNormalizedGaussianInterpolationCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpFibersCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkWarpFibersCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkHessianTensorImageCalculatorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkHessianTensorImageCalculatorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleTensorImageCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleTensorImageCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleTensorImage2Command.h
    ${CMAKE_SOURCE_DIR}/Commands/itkResampleTensorImage2CommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorToScalarCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorToScalarCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorsToDWICommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorsToDWICommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkSyntheticTensorFieldGeneratorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkSyntheticTensorFieldGeneratorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkBoostTensorAnisotropyCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkBoostTensorAnisotropyCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAverageStdTensorCalculatorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkAverageStdTensorCalculatorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorGradientMagnitudeCalculatorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorGradientMagnitudeCalculatorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkNormalize2TensorsCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkNormalize2TensorsCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkScaleTensorCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkScaleTensorCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkComputeBundleStatisticsCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkComputeBundleStatisticsCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDemonsTensorRegistrationCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkDemonsTensorRegistrationCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkLogDomainDemonsTensorRegistrationCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkLogDomainDemonsTensorRegistrationCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkExtractBundleWithROICommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkExtractBundleWithROICommandFactory.h
    )


###############################################
## DEFINE DEPENDENCIES
set(LIBRARIES
    TTK::ITKProgramFactory
    TTK::ITKTensor
    TTK::ttkAlgorithms
    ${ITKIO_LIBRARIES}
    ITKStatistics
	ITKSmoothing
    ${ITK_TRANSFORM_LIBRARIES}
    ${VTK_LIBRARIES}
    ${TTK_LAPACK_LIBRARIES}
  )
    
# Create ttkCommands library
ADD_LIBRARY(                ${TARGET_NAME} ${TTK_BUILD_TYPE})
TARGET_LINK_LIBRARIES(      ${TARGET_NAME} PUBLIC  ${LIBRARIES})
TARGET_SOURCES(             ${TARGET_NAME} PRIVATE ${${TARGET_NAME}_SRCS})
TARGET_SOURCES(             ${TARGET_NAME} PUBLIC 
                              FILE_SET publicHeadersTTKCommands
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

SET (FILESET_INSTALL_DIR_publicHeadersTTKCommands Commands)
                              
export_and_install_libs(${TARGET_NAME})