CC = g++
CFLAGS = -c -Wall
LDFLAGS = -shared

SRCS = ./Source
HEADERS = ./Source/API
OBJS = population.o tournament_selection.o stochastic.o genetic_factory.o galapagos.o
TARGET_LIB = galapagos.so

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET_LIB) $(OBJS)

galapagos.o: $(SRCS)/galapagos.cpp $(HEADERS)/Factory/genetic_factory.h
	$(CC) $(CFLAGS) $(SRCS)/galapagos.cpp

genetic_factory.o: $(SRCS)/Factory/genetic_factory.cpp
	$(CC) $(CFLAGS) $(SRCS)/Factory/genetic_factory.cpp

tournament_selection.o: $(SRCS)/SelectionAlgorithms/tournament_selection.cpp
	$(CC) $(CFLAGS) $(SRCS)/SelectionAlgorithms/tournament_selection.cpp

population.o: $(SRCS)/population.cpp $(HEADERS)/Factory/genetic_factory.h
	$(CC) $(CFLAGS) $(SRCS)/population.cpp

stochastic.o: $(SRCS)/stochastic.cpp
	$(CC) $(CFLAGS) $(SRCS)/stochastic.cpp

clean:
	-rm -f $(TARGET_LIB) $(OBJS) $(TARGET_LIB)
