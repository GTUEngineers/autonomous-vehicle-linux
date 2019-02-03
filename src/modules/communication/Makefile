FLAGS := -g -ansi -pedantic -Wall --std=c++11  
SRCS := source/Server.cpp source/Client.cpp source/AbstractCommunication.cpp Taslak_Main/driver.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)
BIN  := binaries

.PHONY: all clean

all: output

output: $(OBJS)
	$(CXX) $(FLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(FLAGS) -c -MMD -o $@ $<

clean:
	$(RM) output $(OBJS) $(DEPS)

-include $(DEPS)
