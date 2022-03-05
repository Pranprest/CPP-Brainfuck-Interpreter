CC=clang++
CFLAGS=-g -Wall -Werror --std=c++17
SRC=src
BUILD=build
BIN = bfi

all: $(BIN)

# Pretty useful for figuring out how stuff works!
#test: $(SRC)/test.cpp
#	$(CC) $(CFLAGS) $< -o $(BUILD)/$@.o && $(BUILD)/$@.o

bfi: $(SRC)/bfi.cpp $(SRC)/bfi.hpp
	$(CC) $(CFLAGS) $< -o $(BUILD)/$@.o 

# build everything .cpp in src
%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) $(SRC)/$^ -o $(BUILD)/$@.o

clean: $(BUILD)/*.o
	rm $(BUILD)/*.o || echo "Error: No output files found." && echo "Cleaned!"

run: bfi exec 
	
exec: $(BUILD)/bfi.o
	$<