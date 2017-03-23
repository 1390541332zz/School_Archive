PROJ := lab8
SRC := src
BUILD := build

CXXFLAGS := -c -Wall -Wextra -Wpedantic -Werror -pthread -ggdb \
		 	-fsanitize=undefined
LDFLAGS := -lubsan
ifdef ASAN
CXXFLAGS += -fsanitize=address -fsanitize=leak
LDFLAGS := -lasan $(LDFLAGS)
endif

SOURCES := $(SRC)/$(PROJ).cpp $(subst $(SRC)/$(PROJ).cpp,, $(wildcard $(SRC)/*.cpp))
OBJECTS := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))
EXECUTABLE := $(BUILD)/$(PROJ)

#-----------------#
# Build Functions #
#-----------------#

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@


#----------------------------------#
# Cleaning and Archiving Functions #
#----------------------------------#
clean:
	$(RM) $(BUILD)/* $(DIFFTESTOUT)/* $(PROJ).tar

tar: $(PROJ).tar

$(PROJ).tar:
	tar -cvf $(PROJ).tar --xform='s,$(SRC)/,,' \
	$(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*.h)

#---------------------------#
# Diff Tests and Unit Tests #
#---------------------------#
DIFFFLAGS := -ys --suppress-common-lines
DIFFTESTOUT := test/generated
DIFFTESTSAMPLES := test/samples
DIFFTESTS := $(subst .in,, $(subst $(DIFFTESTSAMPLES)/,, $(wildcard $(DIFFTESTSAMPLES)/test*.in)))

test: difftest

difftest: $(EXECUTABLE)
	-@for ver in $(DIFFTESTS); do \
		$(EXECUTABLE) $(DIFFTESTSAMPLES)/$$ver.in $(DIFFTESTOUT)/$$ver.out; \
		diff $(DIFFFLAGS) $(DIFFTESTOUT)/$$ver.out $(DIFFTESTSAMPLES)/$$ver.out; \
	done