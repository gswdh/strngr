# Makefile for strngr library with Unity testing framework
# Compiles for desktop (PC) environment for testing

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -g -O0
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS =

# Directories
SRC_DIR = .
TEST_DIR = tests
UNITY_DIR = $(TEST_DIR)/unity
BUILD_DIR = build
COVERAGE_DIR = coverage_report

# Source files
LIB_SRC = $(SRC_DIR)/strngr.c
LIB_OBJ = $(BUILD_DIR)/strngr.o

# Test files
TEST_SRC = $(TEST_DIR)/test_strngr.c
TEST_RUNNER = $(TEST_DIR)/AllTests.c
UNITY_SRC = $(UNITY_DIR)/unity.c
TEST_OBJ = $(BUILD_DIR)/test_strngr.o
RUNNER_OBJ = $(BUILD_DIR)/AllTests.o
UNITY_OBJ = $(BUILD_DIR)/unity.o

# Test executable
TEST_EXEC = $(BUILD_DIR)/test_runner

# Coverage files
COVERAGE_INFO = $(BUILD_DIR)/coverage.info

.PHONY: all test coverage clean help

all: $(TEST_EXEC)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile library with coverage
$(LIB_OBJ): $(LIB_SRC) $(SRC_DIR)/strngr.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

# Compile Unity framework
$(UNITY_OBJ): $(UNITY_SRC) $(UNITY_DIR)/unity.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test file
$(TEST_OBJ): $(TEST_SRC) $(SRC_DIR)/strngr.h $(UNITY_DIR)/unity.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -I$(SRC_DIR) -I$(UNITY_DIR) -c $< -o $@

# Compile test runner
$(RUNNER_OBJ): $(TEST_RUNNER) $(UNITY_DIR)/unity.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(UNITY_DIR) -c $< -o $@

# Link test executable
$(TEST_EXEC): $(LIB_OBJ) $(TEST_OBJ) $(RUNNER_OBJ) $(UNITY_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $^ -o $@

# Run tests
test: $(TEST_EXEC)
	@echo "Running tests..."
	@./$(TEST_EXEC)

# Generate coverage report
coverage: test
	@echo "Generating coverage report..."
	@mkdir -p $(COVERAGE_DIR)
	@lcov --capture --directory $(BUILD_DIR) --output-file $(COVERAGE_INFO) --rc lcov_branch_coverage=1
	@lcov --remove $(COVERAGE_INFO) '/usr/*' --output-file $(COVERAGE_INFO)
	@genhtml $(COVERAGE_INFO) --output-directory $(COVERAGE_DIR) --branch-coverage
	@echo "Coverage report generated in $(COVERAGE_DIR)/index.html"

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(COVERAGE_DIR)
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "*.gcov" -delete

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build test executable (default)"
	@echo "  test      - Build and run tests"
	@echo "  coverage  - Build, run tests, and generate coverage report"
	@echo "  clean     - Remove all build artifacts and coverage files"
	@echo "  help      - Show this help message"

