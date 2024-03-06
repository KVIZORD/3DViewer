PROJECT_NAME = 3DViewer
TEST_NAME = 3DViewerTests
BUILD_DIR = build

OS = $(shell uname -s)
MACOS = Darwin

ifeq ($(OS), $(MACOS))
MEMORY_TEST = leaks -atExit --
else 
MEMORY_TEST = valgrind --trace-children=yes --leak-check=yes --track-origins=yes
endif


all: install

install: build
	cmake --build $(BUILD_DIR) --target $(PROJECT_NAME)
	$(BUILD_DIR)/src/$(PROJECT_NAME)

uninstall:
	rm -rf $(BUILD_DIR)

build:
	cmake -B $(BUILD_DIR)

clean:
	rm -rf $(PROJECT_NAME).tar

tests: build
	cmake --build $(BUILD_DIR) --target $(TEST_NAME)
	$(BUILD_DIR)/tests/$(TEST_NAME)

leaks: tests
	$(MEMORY_TEST) $(BUILD_DIR)/tests/$(TEST_NAME) --gtest_filter=-*.Throw*

stylecheck: build
	cmake --build $(BUILD_DIR) --target stylecheck

cppcheck: build
	cmake --build $(BUILD_DIR) --target cppcheck

format: build
	cmake --build $(BUILD_DIR) --target format