# the directories where the source files are located
SRC_DIR = src/
INC_DIR = include/
TEST_DIR = test/

# source and header files
SRCS = $(wildcard $(SRC_DIR)*.cpp)
HDRS = $(wildcard $(INC_DIR)*.h)
TESTS = $(wildcard $(TEST_DIR)*.cpp)

# other variables
TARGET = bin/main
TEST_TARGET = bin/run_tests

# default target
all: $(TARGET)

# application target
$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# test target
$(TEST_TARGET): $(TESTS) $(SRCS) $(HDRS)
	$(CXX) -I ./include -o $(TEST_DIR)utilities_test.o -c $(TEST_DIR)utilities_test.cpp
	$(CXX) -o $(TEST_TARGET) $(SRC_DIR)utilities.cpp $(TEST_DIR)utilities_test.o -lgtest -lgtest_main -pthread

# run tests target
run_tests: $(TEST_TARGET)
	./$(TEST_TARGET)

# clean target
clean:
	$(RM) $(TARGET)
	$(RM) $(TEST_TARGET)
