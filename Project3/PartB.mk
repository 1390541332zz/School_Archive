#-------------------------#
# Configuration Variables #
#-------------------------#
PROJ      := project3_b
SRC       := src/todo
BUILD     := build
TEST_DIR  := test
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
TESTRUNNER := bash ./$(TEST_DIR)/testrunner.sh

SUBMISSION := $(wildcard ./$(SRC)/*)

#--------------------------------#
# Intermediary Working Variables #
#--------------------------------#
SOURCES    := $(subst ./$(SRC)/$(MAIN).cpp,,$(wildcard ./$(SRC)/*.cpp))

HEADERS    := $(wildcard ./$(SRC)/*.hpp) \
			  $(wildcard ./$(SRC)/*.tpp)

OBJECTS    := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))

MAIN_EXE := ./$(BUILD)/$(MAIN)

UNIT_EXE := ./$(BUILD)/$(UNIT_MAIN)

#-------------------------#
# Aggregate Make Commands #
#-------------------------#
all: prep build difftest valgrind

#-------------------#
# Build Application #
#-------------------#
build: prep $(MAIN_EXE)

$(MAIN_EXE): $(MAIN_EXE).o $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(MAIN_EXE).o: $(SRC)/$(MAIN).cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

#-------------------#
# Integration Tests #
#-------------------#
DIFFFLAGS := -ys --suppress-common-lines
DIFFTESTOUT := $(TEST_DIR)/generated
DIFFTESTSAMPLES := $(TEST_DIR)/samples
DIFFTESTS := $(subst .in,,$(subst $(DIFFTESTSAMPLES)/,,\
				$(wildcard $(DIFFTESTSAMPLES)/test*.in)))

difftest: $(MAIN_EXE)
	-@for ver in $(DIFFTESTS); do							\
		$(TESTRUNNER) "" 									\
					  "$(MAIN_EXE)" 						\
					  "./$(DIFFTESTSAMPLES)/$$ver.in"		\
					  "./$(DIFFTESTOUT)/$$ver.out";			\
		diff $(DIFFFLAGS) ./$(DIFFTESTOUT)/$$ver.out 	 	\
						  ./$(DIFFTESTSAMPLES)/$$ver.out;	\
	done

valgrind: $(MAIN_EXE)
	-@for ver in $(DIFFTESTS); do							\
		$(TESTRUNNER) "$(VALGRIND)"							\
				  	  "$(MAIN_EXE)" 						\
				  	  "./$(DIFFTESTSAMPLES)/$$ver.in"		\
				  	  "/dev/null";							\
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
