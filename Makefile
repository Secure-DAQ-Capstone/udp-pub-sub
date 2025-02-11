CXX = g++
CXXFLAGS = -std=c++11

# Simple test
SIMPLE_TEST_TARGET = simple_udp_test
SIMPLE_TEST_SOURCES = test.cpp udp-pub.cpp udp-sub.cpp


# Continuous test
TEST_TARGET = udp_test
TEST_SOURCES = test_role.cpp udp-pub.cpp udp-sub.cpp

# Get broadcast address
BROAD_TARGET = get_broadcast_add
BROAD_SOURCES = get_broadcast_add.cpp


all: $(SIMPLE_TEST_TARGET) $(TEST_TARGET) $(BROAD_TARGET)

$(SIMPLE_TEST_TARGET): $(SIMPLE_TEST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(SIMPLE_TEST_TARGET) $(SIMPLE_TEST_SOURCES)

$(TEST_TARGET): $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES)

$(BROAD_TARGET): $(BROAD_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(BROAD_TARGET) $(BROAD_SOURCES)

test: $(SIMPLE_TEST_TARGET)
	./$(SIMPLE_TEST_TARGET)

run_pub: $(TEST_TARGET)
	./$(TEST_TARGET) pub

run_sub: $(TEST_TARGET)
	./$(TEST_TARGET) sub

clean:
	rm -f $(SIMPLE_TEST_TARGET) $(TEST_TARGET)

run: $(SIMPLE_TEST_TARGET)
	./$(SIMPLE_TEST_TARGET)

broad: $(BROAD_TARGET)
	./$(BROAD_TARGET)

.PHONY: all clean run run_pub run_sub