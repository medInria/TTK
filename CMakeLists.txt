cmake_minimum_required(VERSION 3.24)
set(CMAKE_MACOSX_RPATH OFF)
set(TTK_VERSION_NUMBER 1.4.0)
mark_as_advanced(TTK_VERSION_NUMBER)





project(TTK VERSION ${TTK_VERSION_NUMBER})

## #################################################################
## Set software version
## #################################################################
set(${PROJECT_NAME}_VERSION_MAJOR 1 CACHE STRING "TTK major version number.")
set(${PROJECT_NAME}_VERSION_MINOR 4 CACHE STRING "TTK minor version number.")
set(${PROJECT_NAME}_VERSION_BUILD 0 CACHE STRING "TTK build version number.")
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_BUILD}")

mark_as_advanced(${PROJECT_NAME}_VERSION_MAJOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_MINOR)
mark_as_advanced(${PROJECT_NAME}_VERSION_BUILD)




## #################################################################
## Required dependencies and CMAKE MODULES
## #################################################################
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)
find_package(ITK REQUIRED)
find_package(VTK REQUIRED)

INCLUDE(${ITK_USE_FILE})
INCLUDE(${VTK_USE_FILE})
INCLUDE(ITKLibs)
INCLUDE(export_and_install_libs)
INCLUDE(GenerateExportHeader)

## #################################################################
## Options
## #################################################################
option(BUILD_SHARED_LIBS OFF "Build shared libraries")
option(TTK_USE_GMM       OFF "Use GMM to build registration (tensor demons, log domain tensor demons) module")
option(TTK_USE_MKL       OFF "Use MKL to solve eigensystems")
option(TTK_USE_ACML      OFF "Use ACML to solve eigensystems")

if (BUILD_SHARED_LIBS)
    set(TTK_BUILD_TYPE "SHARED")
else()
    set(TTK_BUILD_TYPE "STATIC")
endif()

if (TTK_USE_GMM)
  find_path(GMM_INCLUDE_DIR gmm/gmm.h)
endif(TTK_USE_GMM)

if  (TTK_USE_MKL AND TTK_USE_ACML)
  message(FATAL_ERROR "Both TTK_USE_MKL and TTK_USE_ACML are set to ON, only one can be used at the same time")
endif ()


set(TTK_LAPACK_LIBRARIES)
if (TTK_USE_MKL)
  find_package(MKL REQUIRED)
  set(TTK_LAPACK_LIBRARIES
  ${MKL_LIBRARIES}
  )
endif(TTK_USE_MKL)

if (TTK_USE_ACML)
  find_package(ACML REQUIRED)
  set(TTK_LAPACK_LIBRARIES
  ${ACML_LIBRARY}
  )
endif(TTK_USE_ACML)


# -----------------------------------------------------------------------------
# Header file used to pass CMake settings to the source code
# -----------------------------------------------------------------------------
configure_file(${PROJECT_SOURCE_DIR}/ttkConfigure.h.in ${PROJECT_BINARY_DIR}/ttkConfigure.h)
install(FILES ${TTK_BINARY_DIR}/ttkConfigure.h DESTINATION include)
include_directories(${TTK_BINARY_DIR})


add_subdirectory(Common)
add_subdirectory(IPF)
add_subdirectory(Algorithms)
add_subdirectory(Registration)
add_subdirectory(Commands)

set(PACKAGE_INIT "@PACKAGE_INIT@")
if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in)
	
    configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in "${CMAKE_BINARY_DIR}/lib/cmake/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake" INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}ModuleLocation.cmake ${CMAKE_BINARY_DIR}/lib/cmake/${PROJECT_NAME} COPYONLY)
    INSTALL(FILES "${CMAKE_BINARY_DIR}/lib/cmake/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake" DESTINATION lib/cmake/${PROJECT_NAME})
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}ModuleLocation.cmake DESTINATION  lib/cmake/${PROJECT_NAME})

endif()