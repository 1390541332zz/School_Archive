PROJ  := project0
SRC   := src
BUILD := build
CATCH_DIR := ../../Catch/include/

JOBCOUNT := 9

CPPFLAGS  :=

SANLFLAG  := -lubsan
LDFLAGS   := $(SANLFLAG)

WARNFLAGS := -Wall -Wextra -Wpedantic -Werror
SANFLAG   := -fsanitize=undefined
CXXFLAGS  := -std=c++11  -pedantic -ggdb $(WARNFLAGS) $(SANFLAG)

VALGRIND  := valgrind --tool=memcheck --leak-check=full --show-reachable=yes \
			--num-callers=20 --track-fds=yes --track-origins=yes

SOURCES    := $(wildcard $(SRC)/*.cpp)
HEADERS    := $(wildcard $(SRC)/*.hpp)
OBJECTS    := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))
EXECUTABLE := $(BUILD)/$(PROJ)

all: build test
test: catch valgrind

prep:
	mkdir -p ./build
	$(CXX) --version


#-------------------#
# Build Application #
#-------------------#

build: prep $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX)  $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) -I$(CATCH_DIR) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

#------------#
# Unit Tests #
#------------#
catch: build
	$(EXECUTABLE)

valgrind: build
	$(VALGRIND) $(EXECUTABLE)

gdb: build
	gdb --args $(EXECUTABLE)

#----------------------------------#
# Cleaning and Archiving Functions #
#----------------------------------#
clean:
	$(RM) ./$(BUILD)/* ./$(PROJ).tar ./$(PROJ).zip ./vgcore.* ./.gdb_history*

tar: $(PROJ).tar
zip: $(PROJ).zip

$(PROJ).tar:
	tar -cvf $(PROJ).tar --xform='s,$(SRC)/,,' $(SOURCES) $(HEADERS)

$(PROJ).zip:
	7z a -tzip $(PROJ).zip ./$(SRC)/*
