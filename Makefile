CXX=g++
CFLAGS=-Wall -std=c++11
SRC=uint128_t.cpp
OBJ=$(SRC:.cpp=.o)
TARGET=main

$(TARGET): $(TARGET).cpp $(OBJ)
	$(CXX) $(CFLAGS) $(TARGET).cpp $(OBJ) -o $(TARGET)

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
