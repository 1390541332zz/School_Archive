CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=lab4.cpp calculate.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lab4

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS) $(EXECUTABLE).zip

export:
	zip lab4.zip calculate.cpp calculate.h
