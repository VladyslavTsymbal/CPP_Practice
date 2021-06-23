CXXFLAGS  := -g -std=c++17

.PHONY: all
all: test

test: test.cpp vector.hpp
	$(CXX) $< $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	$(RM) test
