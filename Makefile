CXXFLAGS := -std=c++17 -Ofast

all: trade

trade: trading.cpp
	$(CXX) $(CXXFLAGS) $< -o trade

reduce: jumps.cpp
	$(CXX) $(CXXFLAGS) $< -o reduce

clean:
	rm -f trade reduce