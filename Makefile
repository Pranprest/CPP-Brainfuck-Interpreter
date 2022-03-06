CC=clang++
CFLAGS=-g -Wall -Werror -Wunreachable-code --std=c++17
SRC=src
BUILD=build
BIN = bfi

all: $(BIN)

bfi: $(SRC)/bfi.cpp $(SRC)/bfi.hpp
	$(CC) $(CFLAGS) $< -o $(BUILD)/$@.o 

clean: $(BUILD)/*.o
	rm $(BUILD)/*.o || echo "Error: No output files found." && echo "Cleaned!"

run: bfi exec 
	
exec: $(BUILD)/bfi.o 
	$< $(ARGS)

release: $(SRC)/bfi.cpp $(SRC)/bfi.hpp
	$(CC) $(CFLAGS) -O2 $< -o $(BUILD)/bfi