add_subdirectory(ttkCommands)
add_subdirectory(ttkConvertCommands)
add_subdirectory(ttkUtilCommands)

if(BUILD_EXECUTABLES)
    add_subdirectory(exe_ttk)
    add_subdirectory(exe_ttk-convert)
    add_subdirectory(exe_ttk-utils)
    add_subdirectory(exe_itkStanleyToITK)

    if (TTK_USE_GMM)
        add_subdirectory(exe_DemonsRegistrationTensor)
        add_subdirectory(exe_AssessRegistrationTensor)
        add_subdirectory(exe_LogDomainDemonsRegistrationTensor)
    endif()
endif()
#  
#    # registration commands
#    if (TTK_USE_GMM)
#  
#      add_executable(AssessRegistrationTensor
#        AssessRegistrationTensor.cxx
#        )
#  
#      add_executable(DemonsRegistrationTensor
#        DemonsRegistrationTensor.cxx
#        )
#  
#      add_executable(LogDomainDemonsRegistrationTensor
#        LogDomainDemonsRegistrationTensor.cxx
#        )
#  
#      target_link_libraries(AssessRegistrationTensor
#        ${TTK_MIPS_LIBRARIES}
#        ${TTK_VTKINRIA3D_LIBRARIES}
#        ${TTK_LAPACK_LIBRARIES}
#        ${ITKIO_LIBRARIES}
#        ITKTensor
#        ${VTK_LIBRARIES}
#        )
#      target_link_libraries(DemonsRegistrationTensor
#        ${TTK_MIPS_LIBRARIES}
#        ${TTK_VTKINRIA3D_LIBRARIES}
#        ${TTK_LAPACK_LIBRARIES}
#        ${ITKIO_LIBRARIES}
#        ${ITK_TRANSFORM_LIBRARIES}
#        ITKTensor
#        ${VTK_LIBRARIES}
#        )
#      target_link_libraries(LogDomainDemonsRegistrationTensor
#        ${TTK_MIPS_LIBRARIES}
#        ${TTK_VTKINRIA3D_LIBRARIES}
#        ${TTK_LAPACK_LIBRARIES}
#        ${ITKIO_LIBRARIES}
#        ${ITK_TRANSFORM_LIBRARIES}
#        ITKTensor
#        ${VTK_LIBRARIES}
#        )
#  
#    endif (TTK_USE_GMM)
#  
