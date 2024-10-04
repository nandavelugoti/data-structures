CC=gcc
CFLAGS=-g
LDFLAGS=

all: trie

bin/trie: trie.c.o
	$(CC) $(CFLAGS) $(LDFLAGS) $? -o $@

.PHONY: clean
clean:
	rm -rf bin/
