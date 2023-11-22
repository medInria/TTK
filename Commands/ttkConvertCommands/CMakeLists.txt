set(TARGET_NAME ttkConvertCommands)

###############################################
## DEFINE SOURCES FILES
set(${TARGET_NAME}_SRCS
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorConverterCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorConverterCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkVTKFibersToITKGroupSpatialObjectCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkVTKFibersToITKGroupSpatialObjectCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorsToVTKUnstructuredGridCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorsToVTKUnstructuredGridCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkImageConverterCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkImageConverterCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkConsolidateFiberBundleCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkConsolidateFiberBundleCommandFactory.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkNDImageToTensorImageCommand.cxx
    ${CMAKE_SOURCE_DIR}/Commands/itkNDImageToTensorImageCommandFactory.cxx
    )

###############################################
## DEFINE HEADERS FILES
set(${TARGET_NAME}_HEADERS
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorConverterCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorConverterCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkVTKFibersToITKGroupSpatialObjectCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkVTKFibersToITKGroupSpatialObjectCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorsToVTKUnstructuredGridCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkTensorsToVTKUnstructuredGridCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkImageConverterCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkImageConverterCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkConsolidateFiberBundleCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkConsolidateFiberBundleCommandFactory.h
    ${CMAKE_SOURCE_DIR}/Commands/itkNDImageToTensorImageCommand.h
    ${CMAKE_SOURCE_DIR}/Commands/itkNDImageToTensorImageCommandFactory.h
    )

###############################################
## DEFINE DEPENDENCIES
set(LIBRARIES
    ITKProgramFactory
    ITKTensor
    ${ITKIO_LIBRARIES}
    ITKSpatialObjects
    ${VTK_LIBRARIES}
    ${TTK_LAPACK_LIBRARIES}
	TTK::ttkAlgorithms
  )
    
# Create ttkConvertCommands library
ADD_LIBRARY(                ${TARGET_NAME} ${TTK_BUILD_TYPE})
TARGET_LINK_LIBRARIES(      ${TARGET_NAME} PUBLIC  ${LIBRARIES})
TARGET_SOURCES(             ${TARGET_NAME} PRIVATE ${${TARGET_NAME}_SRCS})
TARGET_SOURCES(             ${TARGET_NAME} PUBLIC 
                              FILE_SET publicHeadersTTKConvertCommands
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

SET (FILESET_INSTALL_DIR_publicHeadersTTKConvertCommands Commands)
                              
export_and_install_libs(${TARGET_NAME})













#  if(WIN32)
#     # The files itkImageConverterCommand.cxx and itkDWIBrainMaskExtractorCommand.cxx
#     # cause the following compile-time error using visual studio 2010:
#     #     fatal error C1128: number of sections exceeded object file format limit : compile with /bigobj
#     # The additional flag /bigobj is added to this one file here.
#     foreach(bigobjFile itkImageConverterCommand.cxx and itkDWIBrainMaskExtractorCommand.cxx)
#         get_source_file_property(bigobjFile_COMPILE_FLAGS ${bigobjFile} COMPILE_FLAGS)
#         if (${bigobjFile_COMPILE_FLAGS} STREQUAL NOTFOUND)
#           set_source_files_properties(${bigobjFile} PROPERTIES COMPILE_FLAGS "/bigobj")
#         else (${bigobjFile_COMPILE_FLAGS} STREQUAL NOTFOUND)
#           set_source_files_properties(${bigobjFile} PROPERTIES COMPILE_FLAGS "${bigobjFile_COMPILE_FLAGS} /bigobj")
#         endif (${bigobjFile_COMPILE_FLAGS} STREQUAL NOTFOUND)
#     endforeach(bigobjFile)
#  endif(WIN32)