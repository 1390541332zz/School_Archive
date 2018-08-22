PROJ  := project5
SRC   := src
BUILD := build

JOBCOUNT := 9

LDFLAGS  := -lubsan
CPPFLAGS := 
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -Werror -pedantic -ggdb -fsanitize=undefined

VALGRIND := valgrind --tool=memcheck --leak-check=full --show-reachable=yes \
			--num-callers=20 --track-fds=yes --track-origins=yes

SOURCES    := $(SRC)/$(PROJ).cpp $(filter-out %_gtest.cpp $(SRC)/$(PROJ).cpp, $(wildcard $(SRC)/*.cpp))
HEADERS    := $(wildcard $(SRC)/*.h)
OBJECTS    := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))
EXECUTABLE := $(BUILD)/$(PROJ)

all: build gtest difftest
test: gtest difftest

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

gdb:
	$(MAKE) -j$(JOBCOUNT) -f GTest.mk gdb PROJ=$(PROJ) SRC=$(SRC) BUILD=$(BUILD)


#------------#
# Diff Tests #
#------------#

DIFFFLAGS := -ys --suppress-common-lines
DIFFTESTOUT := test/generated
DIFFTESTSAMPLES := test/samples
DIFFTESTS := $(subst .in,, $(subst $(DIFFTESTSAMPLES)/,, $(wildcard $(DIFFTESTSAMPLES)/test*.in)))

difftest: $(EXECUTABLE)
	-@for ver in $(DIFFTESTS); do \
		$(EXECUTABLE) $(DIFFTESTSAMPLES)/$$ver.in $(DIFFTESTOUT)/$$ver.out; \
		diff $(DIFFFLAGS) $(DIFFTESTOUT)/$$ver.out $(DIFFTESTSAMPLES)/$$ver.out; \
	done

valgrind: $(EXECUTABLE)
	-@for ver in $(DIFFTESTS); do \
		$(VALGRIND) $(EXECUTABLE) $(DIFFTESTSAMPLES)/$$ver.in $(DIFFTESTOUT)/$$ver.out; \
	done
	-@for ver in $(DIFFTESTS); do \
		diff $(DIFFFLAGS) $(DIFFTESTOUT)/$$ver.out $(DIFFTESTSAMPLES)/$$ver.out; \
	done

#----------------------------------#
# Cleaning and Archiving Functions #
#----------------------------------#
clean:
	$(RM) ./$(BUILD)/* ./$(DIFFTESTOUT)/* ./$(PROJ).tar ./vgcore.* ./.gdb_history*

tar: $(PROJ).tar

$(PROJ).tar:
	tar -cvf $(PROJ).tar --xform='s,$(SRC)/,,' $(SOURCES) $(HEADERS)
