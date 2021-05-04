add_library(DragonTCP
SHARED
DragonTCP.cpp
)

target_include_directories(DragonTCP PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(Boost 1.66 REQUIRED
    COMPONENTS system)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(DragonTCP
    PRIVATE Boost::system
    PUBLIC Threads::Threads
)

install(TARGETS DragonTCP DESTINATION lib)
