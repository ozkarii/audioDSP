# export LD_LIBRARY_PATH=/mnt/c/Users/oskar/Desktop/omat_setit/audio/lib:$LD_LIBRARY_PATH

CXX = g++
CXXFLAGS = -Wall -std=c++11 -I/mnt/c/Users/oskar/Desktop/omat_setit/audio/include
LDFLAGS = -L/mnt/c/Users/oskar/Desktop/omat_setit/audio/lib 
LDLIBS = -lfmod -lfmodL

SRCS = AudioPlayer.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = app.bin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)