CXX = g++
CXXFLAGS = -std=c++17 -Ofast -Wall -Werror -g

SRCS = main.cpp Sender.cpp Worker.cpp unableToOpenFileException.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

TARGET = myprogram

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

-include $(DEPS)
