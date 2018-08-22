GTEST_DIR     := ../googletest/googletest
GTEST_HEADERS := $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_   := $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

LDFLAGS  := -lpthread -lubsan
CPPFLAGS := -isystem $(GTEST_DIR)/include -fsanitize=undefined -ggdb
CXXFLAGS := -pthread -fpermissive

SOURCES    := $(SRC)/$(PROJ).cpp $(filter-out %_gtest.cpp $(SRC)/$(PROJ).cpp, $(wildcard $(SRC)/*.cpp))
OBJECTS    := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))
EXECUTABLE := $(BUILD)/$(PROJ)

GTESTSRC := $(subst $(SRC)/$(PROJ).cpp,, $(subst $(SRC)/$(PROJ)_gtest.cpp,, $(wildcard $(SRC)/*.cpp))) $(SRC)/$(PROJ)_gtest.cpp
GTESTOBJ := $(subst $(SRC), $(BUILD), $(GTESTSRC:.cpp=.o))

TEST_REPETITION_AMOUNT = 20

all: gtest
gtest: $(EXECUTABLE)_gtest
	$(EXECUTABLE)_gtest --gtest_repeat=$(TEST_REPETITION_AMOUNT) --gtest_break_on_failure

gdb: $(EXECUTABLE)_gtest
	gdb --args $(EXECUTABLE)_gtest --gtest_repeat=$(TEST_REPETITION_AMOUNT) --gtest_break_on_failure


$(EXECUTABLE)_gtest: $(GTESTOBJ) $(BUILD)/gtest_main.a
	$(CXX) $(LDFLAGS) $(GTESTOBJ) $(BUILD)/gtest_main.a -o $@
	
$(BUILD)/%.o: $(SRC)/%.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS_GTEST) \
	-c $(GTEST_DIR)/src/gtest-all.cc -o $@

$(BUILD)/gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS_GTEST) \
	-c $(GTEST_DIR)/src/gtest_main.cc -o $@

$(BUILD)/gtest.a: $(BUILD)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILD)/gtest_main.a: $(BUILD)/gtest-all.o $(BUILD)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^