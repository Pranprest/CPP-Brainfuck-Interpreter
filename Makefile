CC=clang++
CFLAGS=-g -Wall -Werror -Wunreachable-code --std=c++17
SRC=src
BUILD=build
BIN = bfi

all: $(BIN)

bfi: $(SRC)/$(BIN).cpp $(SRC)/$(BIN).hpp
	mkdir -p ./build/ && $(CC) $(CFLAGS) $< -o $(BUILD)/$@

clean: $(BUILD)/*.o
	rm $(BUILD)/*.o || echo "Error: No output files found." && echo "Cleaned!"

run: bfi exec 
	
exec: $(BUILD)/$(BIN)
	$< $(ARGS)

release: $(SRC)/$(BIN).cpp $(SRC)/$(BIN).hpp
	$(CC) $(CFLAGS) -O3 $< -o $(BUILD)/$(BIN)