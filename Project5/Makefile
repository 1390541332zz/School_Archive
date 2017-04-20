PROJ  := project5
SRC   := src
BUILD := build

JOBCOUNT := 9

LDFLAGS  := -lubsan
CPPFLAGS := 
CXXFLAGS := -Wall -Wextra -Wpedantic -Werror -ggdb -fsanitize=undefined

SOURCES    := $(SRC)/$(PROJ).cpp $(subst $(wildcard $(SRC)/*_gtest.cpp),, $(subst $(SRC)/$(PROJ).cpp,, $(wildcard $(SRC)/*.cpp)))
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

	
#----------------------------------#
# Cleaning and Archiving Functions #
#----------------------------------#
clean:
	$(RM) ./$(BUILD)/* ./$(DIFFTESTOUT)/* ./$(PROJ).tar ./vgcore.*

tar: $(PROJ).tar

$(PROJ).tar:
	tar -cvf $(PROJ).tar --xform='s,$(SRC)/,,' $(SOURCES) $(HEADERS)
