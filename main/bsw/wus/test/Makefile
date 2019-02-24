TARGET = test
LIBS = -lm
CC = gcc
INCLUDES = -I../
CFLAGS = -g -Wall -ggdb3

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) $(patsubst %.c, %.o, $(wildcard ../*.c)) $(patsubst %.c, %.o, $(wildcard ../../../rte/commander/*.c)) 
HEADERS = $(wildcard *.h) $(wildcard ../*.h) $(wildcard ../../../os/*.hpp) $(wildcard ../../../os/*.h) 

%.o: %.c $(HEADERS)
	echo Building Object File
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) $(INCLUDES) -o $@

clean:
	-rm -f *.o
	-rm -f ../../../rte/commander/*.o
	-rm -f $(TARGET).exe
