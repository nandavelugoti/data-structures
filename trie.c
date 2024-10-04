#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie {
	char ch;
	struct trie **children;
	int child_count;
	char *content;
};

struct trie* find(char ch, struct trie *node) {
	for(int i=0; i<node->child_count; i++)
		if(node->children[i]->ch == ch)
			return node->children[i];
	return NULL;
}

struct trie* create(char ch) {
	struct trie *node= (struct trie*) malloc(sizeof(struct trie));
	node->ch = ch;
	node->children = (struct trie**) malloc(sizeof(struct trie*));
	node->child_count = 0;
	node->content = NULL;
	return node;
}

void link(struct trie *parent, struct trie* child) {
	parent->children = (struct trie**) realloc(parent->children, sizeof(struct trie*) * (parent->child_count+1));
	parent->children[parent->child_count] = child;
	parent->child_count++;
}

void add_word(struct trie *root, char *word, char *content) {
	int word_len = strlen(word);
	struct trie *curr = root;
	struct trie *next = NULL;
	for(int i=0; i<word_len; i++) {
		next = find(word[i], curr);
		if(next == NULL) {
			next = create(word[i]);
			link(curr, next);
		}
		curr = next;
		if(i == word_len-1) {
			curr->content = (char *) malloc(sizeof(char)*strlen(content));
			strcpy(curr->content, content);
		}
	}
}

void print_trie(struct trie *root, int level) {
	for(int i=0; i<level; i++)
		printf("-");
	printf("%c\n", root->ch);
	for(int i=0; i<root->child_count; i++)
		print_trie(root->children[i], level+1); 
}

int main(int argc, char **argv) {
	struct trie *root = create('*'); 
	char word[100], content[1000], dump;
	while(scanf("%s %[^\n]s", &word, &content) != EOF) {
		add_word(root, word, content);
	}
	print_trie(root, 0);
	return 0;
}
