CXX       = g++
CXXFLAGS  = -Wall -I. 
LDFLAGS	  = -fopenmp

PROGRAM_0 = virusim_0
PROGRAM_1 = virusim_1
PROGRAM_2 = virusim_2
SRCS      = src/Random.cpp src/Population.cpp
OBJS      = $(SRCS:.cpp=.o)

.SUFFIXES: .cpp .o

.cpp.o: 
	$(CXX) -c $(CXXFLAGS) $<

all: $(PROGRAM_0) $(PROGRAM_1) $(PROGRAM_2)

$(PROGRAM_0): $(OBJS)
	$(CXX) -o $(PROGRAM_0) virusim-tipo-0.cpp $(SRCS) $(CXXFLAGS) $(LDFLAGS)

$(PROGRAM_1): $(OBJS)
	$(CXX) -o $(PROGRAM_1) virusim-tipo-1.cpp $(SRCS) $(CXXFLAGS) $(LDFLAGS)

$(PROGRAM_2): $(OBJS)
	$(CXX) -o $(PROGRAM_2) virusim-tipo-2.cpp $(SRCS) $(CXXFLAGS) $(LDFLAGS)
	/bin/rm -f *.o

clean:
	/bin/rm -f *.o $(PROGRAM_0) $(PROGRAM_1) $(PROGRAM_2)
