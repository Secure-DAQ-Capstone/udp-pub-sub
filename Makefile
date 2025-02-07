CXX = g++
CXXFLAGS = -std=c++11
TEST_TARGET = udp_test
TEST_SOURCES = test.cpp udp-pub.cpp udp-sub.cpp

all: $(TEST_TARGET)


$(TEST_TARGET): $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET)

run: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean run