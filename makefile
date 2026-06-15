CXX = g++
CXXFLAGS = -std=c++20 -Wall -DDEBUG

SRCS = attack.cpp board.cpp game.cpp init.cpp io.cpp makemove.cpp movegen.cpp perft.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = game

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)