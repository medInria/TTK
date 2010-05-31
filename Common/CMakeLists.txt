add_library(ITKTensor ${TTK_BUILD_TYPE}
  itkNumericTraitsTensorPixel2.cxx
  )

target_link_libraries(ITKTensor
  ITKCommon
  ${TTK_LAPACK_LIBRARIES}
  )

install(TARGETS ITKTensor 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )


file(GLOB __files1 "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
  file(GLOB __files2 "${CMAKE_CURRENT_SOURCE_DIR}/*.txx")
  file(GLOB __files3 "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
  install(FILES ${__files1} ${__files2} ${__files3}
    DESTINATION include
    COMPONENT   Development
  )