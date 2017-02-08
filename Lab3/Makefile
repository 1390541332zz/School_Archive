CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=lab3.cpp resistors.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lab3

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS) $(EXECUTABLE).zip

export:
	zip lab3.zip resistors.cpp resistors.h
