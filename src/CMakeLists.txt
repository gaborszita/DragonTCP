add_library(DragonTCP
SHARED
tcp.cpp
)

target_include_directories(DragonTCP
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

install(TARGETS DragonTCP DESTINATION lib/DragonTCP)