CC=gcc
CFLAGS=-g
LDFLAGS=

all: build build/trie 

build/trie: src/trie.c 
	$(CC) $(CFLAGS) $(LDFLAGS) $? -o $@

build:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
