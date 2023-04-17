CXXFLAGS=-Wall -Wextra -std=c++17
LIBS=`pkg-config libsystemd --cflags --libs`

notify: notify.cpp
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@