#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie {
	char ch;
	struct trie **children;
	int child_count;
	char *content;
};

struct trie* get_child(char ch, struct trie *node) {
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
		next = get_child(word[i], curr);
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

char* get_meaning(char* word, struct trie *root) {
	struct trie *child = get_child(word[0], root);
	if(child == NULL) return NULL;
	if(strlen(word) == 1) return child->content; // This is bad!! Should return a copy, not the reference! 
	return get_meaning(&word[0], child);
}

int main(int argc, char **argv) {
	struct trie *root = create('*'); 
	char word[100], content[1000], dump;
	printf("dictionary loading ...\n");
	while(scanf("%s %[^\n]s", word, content) != EOF) {
		add_word(root, word, content);
	}
	add_word(root, word, content);
	printf("done.\n");
	//print_trie(root, 0);
	printf("Type a word for a meaning\n");
	while(scanf("%[^\n]s", word) != EOF) {
		scanf("%s", word);
		char* meaning = get_meaning(word, root);
		if (meaning == NULL) printf("%s: WORD NOT FOUND!\n\n", word);
		else printf("%s\n\n", meaning);
	}
	return 0;
}
