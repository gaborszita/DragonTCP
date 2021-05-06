include(CMakeFindDependencyMacro)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_dependency(Threads)
find_dependency(Boost 1.66 COMPONENTS system)

include("${CMAKE_CURRENT_LIST_DIR}/DragonTCPTargets.cmake")
