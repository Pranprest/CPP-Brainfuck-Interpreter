CC=clang++
CFLAGS=-g -Wall
SRC=src
BUILD=build
BIN = bfi

all: $(BIN)

bfi: $(SRC)/bfi.cpp
	$(CC) $(CFLAGS) $< -o $(BUILD)/$@.o 

# build everything .cpp in src
%.o: %.cpp #%.h
	$(CC) $(CFLAGS) $(SRC)/$^ -o $(BUILD)/$@

clean: $(BUILD)/*.o
	rm $(BUILD)/*.o || echo "Error: No output files found." && echo "Removed!"

run: bfi exec 
	
exec: $(BUILD)/bfi.o
	$<