PROJ := project3
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

GTEST_DIR = ../googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

test: gtest difftest

difftest: $(EXECUTABLE)
	-@for ver in $(DIFFTESTS); do \
		$(EXECUTABLE) $(DIFFTESTSAMPLES)/$$ver.in $(DIFFTESTOUT)/$$ver.out; \
		diff $(DIFFFLAGS) $(DIFFTESTOUT)/$$ver.out $(DIFFTESTSAMPLES)/$$ver.out; \
	done

gtest: $(GTESTS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc
