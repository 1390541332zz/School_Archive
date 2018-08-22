PROJ  := project5
SRC   := src
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

CALLGRIND := valgrind --tool=callgrind

SOURCES      := $(wildcard $(SRC)/*.cpp)
HEADERS      := $(wildcard $(SRC)/*.hpp) $(wildcard $(SRC)/*.tpp)
OBJECTS      := $(subst $(SRC), $(BUILD), $(SOURCES:.cpp=.o))
EXECUTABLE   := $(BUILD)/$(PROJ)

all: build

prep:
	mkdir -p ./build
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
catch: build
	$(EXECUTABLE)

valgrind: build
	$(VALGRIND) $(EXECUTABLE)

callgrind: build
	$(CALLGRIND) $(EXECUTABLE)

gdb: build
	gdb --args $(EXECUTABLE)

#----------------------------------#
# Cleaning and Archiving Functions #
#----------------------------------#
clean:
	$(RM) ./$(BUILD)/*			\
		  ./$(PROJ).zip			\
		  ./vgcore.*			\
		  ./callgrind.out.*		\
		  ./.gdb_history*

zip: $(PROJ).zip

$(PROJ).zip:
	mkdir ./$(BUILD)/zip
	cp ./$(SRC)/MinPriorityQueue.tpp ./$(BUILD)/zip/MinPriorityQueue.cpp
	cp ./$(SRC)/*.cpp ./$(BUILD)/zip/
	cp ./$(SRC)/*.hpp ./$(BUILD)/zip/
	find ./$(BUILD)/zip/ -type f | xargs sed -i 's/.tpp/.cpp/g'
	7z a -tzip $(PROJ).zip ./$(BUILD)/zip/*
	rm -rf ./$(BUILD)/zip
