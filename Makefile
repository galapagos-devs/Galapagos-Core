CC = gcc
LDFLAGS = -shared

TARGET_LIB = galapagos.so
SRCS = galapagos.c
DEPS = galapagos.h
OBJECTS = galapagos.o #$(SRCS:.c=.o)

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET_LIB) $(OBJECTS)

$(OBJECTS): galapagos.c galapagos.h $(DEPS) #get all headers?
	$(CC) -c galapagos.c galapagos.h
	
.PHONY clean
clean:
	-rm -f $(TARGET_LIB) $(OBJS)