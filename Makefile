CC=gcc
CFLAGS=-g
LDFLAGS=

all: build build/trie build/avl_tree

build:
	mkdir -p $@

build/trie: src/trie.c 
	$(CC) $(CFLAGS) $(LDFLAGS) $? -o $@

build/avl_tree: src/avl_tree.c
	$(CC) $(CFLAGS) $(LDFLAGS) $? -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
