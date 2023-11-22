set(TARGET_NAME AssessRegistrationTensor)

###############################################
## DEFINE SOURCES FILES
set(${TARGET_NAME}_SRCS
    ${CMAKE_SOURCE_DIR}/Commands/AssessRegistrationTensor.cxx
    )

###############################################
## DEFINE DEPENDENCIES
set(LIBRARIES
    ${TTK_LAPACK_LIBRARIES}
    ${ITKIO_LIBRARIES}
    ITKTensor
    ${VTK_LIBRARIES}
  )
    
# Create ttkUtilCommands library
ADD_EXECUTABLE(             ${TARGET_NAME} )
TARGET_LINK_LIBRARIES(      ${TARGET_NAME} PRIVATE  ${LIBRARIES})
TARGET_SOURCES(             ${TARGET_NAME} PRIVATE ${${TARGET_NAME}_SRCS})
                              
export_and_install_libs(${TARGET_NAME})

