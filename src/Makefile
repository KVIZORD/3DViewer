BUILD_DIR = build
VIEW_DIR = view
MODEL_DIR = model
PROJECT_EXE = 3d_viewer
TEST_DIR = tests
TEST_EXE = test
CXX = g++
CFLAGS = -Werror -Wextra -Wall
LIBS = -lgtest
MEMORY_TEST = 
OS = $(shell uname -s)
MACOS = Darwin

ifeq ($(OS), $(MACOS))
PROJECT_EXE = 3d_viewer.app
MEMORY_TEST = leaks -atExit --
else 
MEMORY_TEST = valgrind --trace-children=yes --leak-check=yes --track-origins=yes
LIBS += -lsubunit -lrt -lm -lpthread
endif

.PHONY: all install dvi uninstall tests clean autoformat dist clean_tests

all: install

install: $(BUILD_DIR)
	cd $(VIEW_DIR) && qmake && make
	mv $(VIEW_DIR)/$(PROJECT_EXE) $(BUILD_DIR)

uninstall: clean
	rm -rf $(BUILD_DIR)

tests: $(MODEL_DIR)/objreaderfast.o $(MODEL_DIR)/scene.o $(MODEL_DIR)/transform_matrix.o $(MODEL_DIR)/transform_matrix_builder.o
	mv *.o $(TEST_DIR)
	cd $(TEST_DIR) && $(CXX) $(CFLAGS) *.cc *.o -o $(TEST_EXE) $(LIBS)
	$(TEST_DIR)/$(TEST_EXE)

clean_tests:
	rm -rf $(TEST_DIR)/*.o $(TEST_DIR)/$(TEST_EXE)

clean: clean_tests
	cd $(VIEW_DIR) && qmake && make clean
	rm -rf $(VIEW_DIR)/.qmake.stash $(VIEW_DIR)/Makefile
	
autoformat:
	find . -type f -name "*.cc" -o -name "*.h" | xargs clang-format -style=Google -i

dist:
	mkdir -p source
	cp -r Makefile view model controller tests obj_examples main.cc source
	tar -cf source.tar source
	rm -rf source

%.o: %.cc
	$(CXX) $(CFLAGS) -c $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

leaks: tests
	$(MEMORY_TEST) $(TEST_DIR)/$(TEST_EXE) --gtest_filter=-*Throw.*
