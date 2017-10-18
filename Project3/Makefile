#-------------------------#
# Configuration Variables #
#-------------------------#
PROJ  := project3
SRC   := src
BUILD := build
UNIT_DIR  := ../../Catch/include/

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

SUBMISSION := $(foreach f, abstract_list.hpp, \
						   $(subst ./$(SRC)/$(f),,$(wildcard ./$(SRC)/*)))

#--------------------------------#
# Intermediary Working Variables #
#--------------------------------#
SOURCES    := $(foreach f, $(MAIN) $(TEST_MAIN), \
						   $(subst $(SRC)/$(f).cpp,,$(wildcard ./$(SRC)/*.cpp)))

HEADERS    := $(wildcard ./$(SRC)/*.hpp) \
			  $(wildcard ./$(SRC)/*.tpp)

OBJECTS    := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))

MAIN_EXE := ./$(BUILD)/$(MAIN)

UNIT_EXE := ./$(BUILD)/$(UNIT_MAIN)

.PHONY: all prep clean zip \
		build-all build build-test \
		unit unit-valgrind unit-gdb \
		difftest valgrind \
		integrationtest unittest

#-------------------------#
# Aggregate Make Commands #
#-------------------------#
all: prep unittest integrationtest

integrationtest: build difftest valgrind

unittest: build-unit unit unit-valgrind



#-------------------#
# Build Application #
#-------------------#
build: prep $(MAIN_EXE)

$(MAIN_EXE): $(MAIN_EXE).o $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(MAIN_EXE).o: $(SRC)/$(MAIN).cpp
	$(CXX) -I$(UNIT_DIR) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

#------------------#
# Build Unit Tests #
#------------------#
build-unit: prep $(UNIT_EXE)

$(UNIT_EXE): $(UNIT_EXE).o $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(UNIT_EXE).o: $(SRC)/$(UNIT_MAIN).cpp
	$(CXX) -I$(UNIT_DIR) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

#------------#
# Unit Tests #
#------------#
unit: $(UNIT_EXE)
	$(UNIT_EXE)

unit-valgrind: $(UNIT_EXE)
	$(VALGRIND) $(UNIT_EXE)

unit-gdb: $(UNIT_EXE)
	gdb --args $(UNIT_EXE)

#------------#
# Diff Tests #
#------------#
DIFFFLAGS := -ys --suppress-common-lines
DIFFTESTOUT := test/generated
DIFFTESTSAMPLES := test/samples
DIFFTESTS := $(subst .in,,$(subst $(DIFFTESTSAMPLES)/,,\
				$(wildcard $(DIFFTESTSAMPLES)/test*.in)))

difftest: $(MAIN_EXE)
	-@for ver in $(DIFFTESTS); do							\
		$(MAIN_EXE) ./$(DIFFTESTSAMPLES)/$$ver.in			\
					./$(DIFFTESTOUT)/$$ver.out;   			\
		diff $(DIFFFLAGS) ./$(DIFFTESTOUT)/$$ver.out 	 	\
						  ./$(DIFFTESTSAMPLES)/$$ver.out;	\
	done

valgrind: $(MAIN_EXE)
	-@for ver in $(DIFFTESTS); do								\
		$(VALGRIND) $(MAIN_EXE) ./$(DIFFTESTSAMPLES)/$$ver.in	\
								/dev/null;						\
	done
#---------------------#
# Ancillary Functions #
#---------------------#
prep:
	mkdir -p ./build
	$(CXX) --version

clean:
	$(RM) ./$(BUILD)/*			\
		  ./$(DIFFTESTOUT)/*	\
		  ./$(PROJ).zip			\
		  ./vgcore.*			\
		  ./.gdb_history*

zip: $(PROJ).zip

$(PROJ).zip:
	7z a -tzip $(PROJ).zip $(SUBMISSION)
