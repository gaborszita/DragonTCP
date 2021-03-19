# DragonTCP
DragonTCP is a simple TCP messaging library. It is based on boost asio. Every data that is being sent needs to have an ID and a message. This is used for routing a specific purpose of a message to a specific function on either the client or server

Plans for patch 2.1.1:
- bug fixes
  - void DragonTCP::DragonTCP::disconnect(boost::system::error_code &error) doesn't call socket.close()'s error code constructor
- Add more comments that explains how the program work. There are very few comments and it is hard to understand how the functions work. 

Plans for version 3.0:
- Migrate build system from Makefile to cmake
- Seperate header files from C++ files
- Seperate example code from the files that will install
- Add support to install on system using cmake install feature
