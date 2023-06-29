CXXFLAGS := -std=c++17 -Ofast

all: trade jump

trade: jumps.cpp
	$(CXX) $(CXXFLAGS) $< -o trade

reduce: reduce.cpp
	$(CXX) $(CXXFLAGS) $< -o reduce

clean:
	rm -f trade reduce