CXXFLAGS=-c -Wall -Wextra -Wpedantic -Werror
LDFLAGS=
SOURCES=$(EXE).cpp $(subst $(EXE).cpp, , $(wildcard *.cpp))
OBJECTS=$(SOURCES:.cpp=.o)
EXE=project1

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) ./$(EXE) ./$(OBJECTS) ./$(EXE).tar ./$(EXE).zip ./output.txt ./vgcore.*

tar:
	tar -cvf $(EXE).tar $(SOURCES) $(wildcard *.h)

zip:
	zip $(EXE).zip $(SOURCES) $(wildcard *.h)
