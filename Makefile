CC=gcc
CXX=g++
LD=g++
CXXFLAGS= -c -Wall -g
LDFLAGS= -Wall -lboost_system
OBJS_COMMON= tcp.o
OBJS_SERVER= mainserver.o
OBJS_CLIENT= mainclient.o
OBJS= $(OBJS_COMMON) $(OBJS_SERVER) $(OBJS_CLIENT)
MAINSERVER_TARGET=mainserver
MAINCLIENT_TARGET=mainclient
TARGETS = $(MAINSERVER_TARGET) $(MAINCLIENT_TARGET)

main: $(TARGETS)

$(MAINSERVER_TARGET): $(OBJS_COMMON) $(OBJS_SERVER)
	$(LD) -o $(MAINSERVER_TARGET) $(OBJS_COMMON) $(OBJS_SERVER) $(LDFLAGS)

$(MAINCLIENT_TARGET): $(OBJS_COMMON) $(OBJS_CLIENT)
	$(LD) -o $(MAINCLIENT_TARGET) $(OBJS_COMMON) $(OBJS_CLIENT) $(LDFLAGS)

mainserver.o: mainserver.cpp
	$(CXX) $(CXXFLAGS) mainserver.cpp
	
mainclient.o: mainclient.cpp
	$(CXX) $(CXXFLAGS) mainclient.cpp

tcp.o: tcp.cpp tcp.h
	$(CXX) $(CXXFLAGS) tcp.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(TARGETS)