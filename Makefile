CXX = g++
CXXFLAGS = -Wall -std=c++17 -g # -g for debugging
LDLIBS = `sdl2-config --cflags --libs`

SRCS = Player.cpp DSP.cpp 
OBJS = $(SRCS:.cpp=.o)
TARGET = app.bin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)