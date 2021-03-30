cmake_minimum_required(VERSION 3.10)

project("DragonTCP examples" VERSION 3.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Server mainserver.cpp)

target_link_libraries(Server
    PRIVATE DragonTCP pthread
)

add_executable(Client mainserver.cpp)

target_link_libraries(Client
    PRIVATE DragonTCP pthread
)