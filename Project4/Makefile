#-------------------------#
# Configuration Variables #
#-------------------------#
PROJ      := project4
SRC       := src
BUILD     := build
TEST_DIR  := test
UNIT_DIR  := ../../Catch/single_include/

JOBCOUNT  := 9

CPPFLAGS  :=

SANLFLAG  := #-lasan -lubsan

LDFLAGS    = $(SANLFLAG)

WARNFLAGS := -Wall -Wextra -Wpedantic -Werror -Wchkp -Wno-sign-compare \
			 -Wno-deprecated

SANFLAG   := #-fsanitize=undefined -fsanitize=address

CXXFLAGS   = -std=c++11  -pedantic -ggdb $(WARNFLAGS) $(SANFLAG)

VALGRIND  := valgrind --tool=memcheck --leak-check=full --show-reachable=yes \
			--num-callers=20 --track-fds=yes --track-origins=yes

MAIN	   := main
UNIT_MAIN  := test_list
TESTRUNNER := bash ./$(TEST_DIR)/testrunner.sh

SUBMISSION := ./$(SRC)/ds/deque.tpp      \
			  ./$(SRC)/ds/deque.hpp      \
			  ./$(SRC)/ds/test_deque.cpp \
			  ./$(SRC)/pathfinder/pathfinder.cpp

#--------------------------------#
# Intermediary Working Variables #
#--------------------------------#
SOURCES    := $(subst ./$(SRC)/$(MAIN).cpp,,$(wildcard ./$(SRC)/*.cpp))

HEADERS    := $(wildcard ./$(SRC)/*.hpp) \
			  $(wildcard ./$(SRC)/*.tpp)

OBJECTS    := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))

MAIN_EXE := ./$(BUILD)/$(MAIN)

UNIT_EXE := ./$(BUILD)/$(UNIT_MAIN)

.PHONY: all  \
		build-all build build-test \
		unit unit-valgrind unit-gdb \
		valgrind \
		integrationtest unittest

#-------------------------#
# Aggregate Make Commands #
#-------------------------#
all: unittest integrationtest

integrationtest: build difftest

unittest: build-unit unit unit-valgrind

build:
	make -f PartB.mk build

build-unit:
	make -f PartA.mk build

unit:
	make -f PartA.mk unit

unit-valgrind:
	make -f PartA.mk valgrind

unit-gdb:
	make -f PartA.mk gdb

valgrind:
	make -f PartB.mk valgrind

callgrind:
	make -f PartB.mk callgrind

difftest:
	make -f PartB.mk difftest

clean:
	make -f PartA.mk clean
	make -f PartB.mk clean
	$(RM) ./$(PROJ).zip

#zip:
#	make -f PartA.mk zip
#	make -f PartB.mk zip

zip: $(PROJ).zip

$(PROJ).zip:
	7z a -tzip $(PROJ).zip $(SUBMISSION)
