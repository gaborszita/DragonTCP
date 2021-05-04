cmake_minimum_required(VERSION 3.10)

set(DragonTCP_VERSION 3.0.1)
project(DragonTCP VERSION ${DragonTCP_VERSION} LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(include)

install(TARGETS DragonTCP EXPORT DragonTCPTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DragonTCP/DragonTCPConfigVersion.cmake"
  VERSION ${DragonTCP_VERSION}
  COMPATIBILITY SameMajorVersion
)

export(EXPORT DragonTCPTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/DragonTCP/DragonTCPTargets.cmake"
  NAMESPACE DragonTCP::
)
configure_file(cmake/DragonTCPConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/DragonTCP/DragonTCPConfig.cmake"
  COPYONLY
)


set(ConfigPackageLocation lib/cmake/DragonTCP)
install(EXPORT DragonTCPTargets
  FILE
    DragonTCPTargets.cmake
  NAMESPACE
    DragonTCP::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    cmake/DragonTCPConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/DragonTCP/DragonTCPConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
)
