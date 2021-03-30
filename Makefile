CC=gcc
CXX=g++
LD=g++
CXXFLAGS= -c -Wall
LDFLAGS= -Wall -lboost_system -pthread
OBJS_COMMON= tcp.o
OBJS_SERVER= mainserver.o
OBJS_CLIENT= mainclient.o
OBJS= $(OBJS_COMMON) $(OBJS_SERVER) $(OBJS_CLIENT)
MAINSERVER_TARGET=mainserver
MAINCLIENT_TARGET=mainclient
TARGETS= $(MAINSERVER_TARGET) $(MAINCLIENT_TARGET)
DEPS= tcp.h

main: $(TARGETS)

$(MAINSERVER_TARGET): $(OBJS_COMMON) $(OBJS_SERVER)
	$(LD) -o $(MAINSERVER_TARGET) $(OBJS_COMMON) $(OBJS_SERVER) $(LDFLAGS)

$(MAINCLIENT_TARGET): $(OBJS_COMMON) $(OBJS_CLIENT)
	$(LD) -o $(MAINCLIENT_TARGET) $(OBJS_COMMON) $(OBJS_CLIENT) $(LDFLAGS)

$(OBJS): %.o : %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(TARGETS)
