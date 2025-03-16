CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

CLASS_OBJ = AVL_TREE.o
CLASS_SRC = AVL_TREE.cpp
CLASS_HEADER = AVL_TREE.h
DEMO_SRC = demo.cpp
TEST_SRC = test.cpp

DEMO_BIN = demo
TEST_BIN = test

TEST_LOG = log.txt

all: build_class build_demo build_test

build_class: $(CLASS_SRC) $(CLASS_HEADER)
	$(CXX) $(CXXFLAGS) -c $(CLASS_SRC)

build_demo: build_class $(DEMO_SRC)
	$(CXX) $(CXXFLAGS) $(CLASS_OBJ) $(DEMO_SRC) -o $(DEMO_BIN)

build_test: build_class $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(CLASS_OBJ) $(TEST_SRC) -o $(TEST_BIN)

run_demo: build_demo
	./$(DEMO_BIN)

run_test: build_test
	./$(TEST_BIN) 2>&1 | tee $(TEST_LOG)

clean:
	rm -f $(DEMO_BIN) $(TEST_BIN) $(CLASS_OBJ) $(TEST_LOG) *.exe

run_all: run_demo run_test