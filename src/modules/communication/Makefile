FLAGS := -g -ansi -pedantic -Wall --std=c++11  
HDR   := header
SRCS := source/Server.cpp source/Client.cpp source/AbstractCommunication.cpp Taslak_Main/driver.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

.PHONY: all clean

all: output

output: $(OBJS)
	$(CXX) $(FLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(FLAGS) -c -MMD -o $@ $<

clean:
	$(RM) output $(OBJS) $(DEPS)

-include $(DEPS)
