PROJ := lab7
MAIN := test

CXXFLAGS := -c -O0 -Wall -Wextra -Wpedantic -Werror
LDFLAGS :=

DIFFFLAGS := -ys --suppress-common-lines

SRC := src
BUILD := build
TESTOUT := test/generated
TESTSAMPLES := test/samples

TESTS := $(subst .in,, $(subst $(TESTSAMPLES)/,, $(wildcard $(TESTSAMPLES)/test*.in)))

SOURCES := $(SRC)/$(MAIN).cpp $(subst $(SRC)/$(MAIN).cpp,, $(wildcard $(SRC)/*.cpp))
OBJECTS := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))
EXECUTABLE := $(BUILD)/$(PROJ)

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) ./$(BUILD)/* ./$(TESTOUT)/* ./$(PROJ).tar ./vgcore.*


test: $(EXECUTABLE)
	-@for ver in $(TESTS); do \
		$(EXECUTABLE) $(TESTSAMPLES)/$$ver.in $(TESTOUT)/$$ver.out; \
		diff $(DIFFFLAGS) $(TESTOUT)/$$ver.out $(TESTSAMPLES)/$$ver.out; \
	done


tar: $(PROJ).tar

$(PROJ).tar:
	tar -cvf $(PROJ).tar --xform='s,$(SRC)/,,' \
	$(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*.h)
