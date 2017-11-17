#-------------------------#
# Configuration Variables #
#-------------------------#
PROJ      := project4_b
SRC       := src/pathfinder
BUILD     := build
TEST_DIR  := test
UNIT_DIR  := ../../Catch/single_include/
DS_DIR  := src/ds

JOBCOUNT  := 9

CPPFLAGS  :=

SANLFLAG  := #-lasan -lubsan

LDFLAGS    = $(SANLFLAG)

WARNFLAGS := -Wall -Wextra -Wpedantic -Werror -Wchkp -Wno-sign-compare \
			 -Wno-deprecated

SANFLAG   := #-fsanitize=undefined -fsanitize=address

CXXFLAGS   = -std=c++11 -pedantic -ggdb $(WARNFLAGS) $(SANFLAG) -I./$(DS_DIR)/

VALGRIND  := valgrind --tool=memcheck --leak-check=full --show-reachable=yes \
			--num-callers=20 --track-fds=yes --track-origins=yes

MAIN	   := pathfinder
TESTRUNNER := bash ./$(TEST_DIR)/testrunner.sh

#SUBMISSION := $(wildcard ./$(SRC)/*)

#--------------------------------#
# Intermediary Working Variables #
#--------------------------------#
SOURCES    := ./$(SRC)/$(MAIN).cpp \
				$(subst ./$(SRC)/compare.cpp,, \
					$(subst ./$(SRC)/$(MAIN).cpp,,$(wildcard ./$(SRC)/*.cpp)))

HEADERS    := $(wildcard ./$(SRC)/*.hpp) \
			  $(wildcard ./$(SRC)/*.tpp)

OBJECTS    := $(subst $(SRC),$(BUILD),$(SOURCES:.cpp=.o))

MAIN_EXE := ./$(BUILD)/$(MAIN)

UNIT_EXE := ./$(BUILD)/$(UNIT_MAIN)

#-------------------------#
# Aggregate Make Commands #
#-------------------------#
all: prep build valgrind

#-------------------#
# Build Application #
#-------------------#
build: prep $(MAIN_EXE)

$(MAIN_EXE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD)/compare: $(BUILD)/compare.o $(OBJECTS)
	$(CXX) $(LDFLAGS) $(BUILD)/compare.o $(BUILD)/image.o $(BUILD)/lodepng.o -o $@

$(BUILD)/%.o: ./$(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/compare.o: ./$(SRC)/compare.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


#-------------------#
# Integration Tests #
#-------------------#
#DIFFFLAGS := -ys --suppress-common-lines
DIFFTESTOUT := $(TEST_DIR)/generated
DIFFTESTSAMPLES := $(TEST_DIR)/samples
DIFFTESTS := $(subst .in.png,,$(subst $(DIFFTESTSAMPLES)/,,\
				$(wildcard $(DIFFTESTSAMPLES)/test*.in.png)))

difftest: $(MAIN_EXE) $(BUILD)/compare
	-@for ver in $(DIFFTESTS); do								\
		$(MAIN_EXE) ./$(DIFFTESTSAMPLES)/$$ver.in.png			\
					./$(DIFFTESTOUT)/$$ver.out.png;				\
		./$(BUILD)/compare ./$(DIFFTESTOUT)/$$ver.out.png 		\
						   ./$(DIFFTESTSAMPLES)/$$ver.out.png;	\
	done

valgrind: $(MAIN_EXE)
	-@for ver in $(DIFFTESTS); do									\
		$(VALGRIND) $(MAIN_EXE) ./$(DIFFTESTSAMPLES)/$$ver.in.png	\
				  	            /dev/null;							\
	done
#---------------------#
# Ancillary Functions #
#---------------------#
prep:
	mkdir -p ./$(BUILD)
	mkdir -p ./$(DIFFTESTOUT)
	$(CXX) --version

clean:
	$(RM) ./$(BUILD)/*			\
		  ./$(DIFFTESTOUT)/*	\
		  ./$(PROJ).zip			\
		  ./vgcore.*			\
		  ./gmon.out			\
		  ./.gdb_history*

#zip: $(PROJ).zip
#
#$(PROJ).zip:
#	7z a -tzip $(PROJ).zip $(SUBMISSION)
