# export LD_LIBRARY_PATH=/mnt/c/Users/oskar/Desktop/omat_setit/audio/lib:$LD_LIBRARY_PATH

CXX = g++
CXXFLAGS = -Wall -std=c++11
LDLIBS = `sdl2-config --cflags --libs`

SRCS = player.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = app.bin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)