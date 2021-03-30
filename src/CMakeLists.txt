add_library(DragonTCP
SHARED
tcp.cpp
)

target_include_directories(DragonTCP
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(DragonTCP
    PRIVATE boost_system
    PUBLIC pthread
)

install(TARGETS DragonTCP DESTINATION lib)