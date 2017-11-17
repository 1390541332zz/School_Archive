PROJ  := project4_a
SRC   := src/ds
BUILD := build
CATCH_DIR := ../../Catch/single_include/

JOBCOUNT := 9

CPPFLAGS  :=

SANLFLAG  := #-lasan -lubsan

LDFLAGS    = $(SANLFLAG)

WARNFLAGS := -Wall -Wextra -Wpedantic -Werror -Wchkp -Wno-sign-compare \
			 -Wno-deprecated

SANFLAG   := #-fsanitize=undefined -fsanitize=address

CXXFLAGS   = -std=c++11  -pedantic -ggdb $(WARNFLAGS) $(SANFLAG)

VALGRIND  := valgrind --tool=memcheck --leak-check=full --show-reachable=yes \
			--num-callers=20 --track-fds=yes --track-origins=yes

SOURCES    := $(wildcard $(SRC)/*.cpp)
HEADERS    := $(wildcard $(SRC)/*.hpp) $(wildcard $(SRC)/*.tpp)
OBJECTS    := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))
EXECUTABLE := $(BUILD)/$(PROJ)

#SUBMISSION := $(foreach f, , \
#						   $(subst ./$(SRC)/$(f),,$(wildcard ./$(SRC)/*)))

all: build

prep:
	mkdir -p ./$(BUILD)
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
unit: build
	$(EXECUTABLE)

valgrind: build
	$(VALGRIND) $(EXECUTABLE)

gdb: build
	gdb --args $(EXECUTABLE)

#----------------------------------#
# Cleaning and Archiving Functions #
#----------------------------------#
clean:
	$(RM) ./$(BUILD)/*			\
		  ./$(PROJ).zip			\
		  ./vgcore.*			\
		  ./.gdb_history*

#zip: $(PROJ).zip
#
#$(PROJ).zip:
#	7z a -tzip $(PROJ).zip $(SUBMISSION)
