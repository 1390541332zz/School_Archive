PROJ  := lab9
SRC   := src
BUILD := build
TEST  := test

JOBCOUNT := 9

LDFLAGS  := #-lubsan
CPPFLAGS := 
CXXFLAGS := -Wall -Wextra -Wpedantic -Werror -ggdb #-fsanitize=undefined

SOURCES    := $(SRC)/$(PROJ).cpp $(subst $(wildcard $(SRC)/*_gtest.cpp),, $(subst $(SRC)/$(PROJ).cpp,, $(wildcard $(SRC)/*.cpp)))
HEADERS    := $(wildcard $(SRC)/*.h)
OBJECTS    := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))
EXECUTABLE := $(BUILD)/$(PROJ)

all: gtest
test: gtest

#-------------------#
# Build Application #
#-------------------#

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

#------------#
# Unit Tests #
#------------#
gtest:
	$(MAKE) -j$(JOBCOUNT) -f GTest.mk PROJ=$(PROJ) SRC=$(SRC) BUILD=$(BUILD)

#----------------------------------#
# Cleaning and Archiving Functions #
#----------------------------------#
clean:
	$(RM) ./$(BUILD)/* ./$(TEST)/generated/* ./$(PROJ).tar ./vgcore.*

tar: $(PROJ).tar

$(PROJ).tar:
	tar -cvf $(PROJ).tar --xform='s,$(SRC)/,,' $(SOURCES) $(HEADERS)
