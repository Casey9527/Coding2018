
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char chr_legal[] = "abcdefghijklmnopqrstuvwxyz";

struct trie_node {
	struct trie_node *next[sizeof(chr_legal) - 1];
	int eow;
};

struct trie_node* trie_node_new()
{
	struct trie_node *node;
	node = calloc(sizeof(struct trie_node), 1);
	if (!node)
		printf("failed to allocate a trie node\n");
	return node;
}

void trie_print(struct trie_node *root, int level)
{
	int i;
	if (!root)
		return;

	for (i = 0; i < strlen(chr_legal); i++) {
		if (root->next[i]) {
			printf("[level, char]: %2d, %c\n", level, chr_legal[i]);
			trie_print(root->next[i], level + 1);
		}
	}

	if (root->eow)
		printf("[level, char]: %2d, eow\n", level);
}

#define trie_insert(r, k)	trie_traverse(r, k, 1)
#define trie_search(r, k)	trie_traverse(r, k, 0)

/*
 * trie_traverse()
 *	insert/search in a trie.
 * @create_on_miss:
 * - 0: search only. Return end node if the key exist. Otherwise, return NULL.
 * - 1: search and create if doesn't exist. Return the end node;
 */
struct trie_node* trie_traverse(struct trie_node *root, const char *key,
								int create_on_miss)
{
	char c;
	while (root) {
		int idx;
		if ((c = key[0]) == '\0') {
			if (!root->eow && !create_on_miss)	/* search mode but not the end of word */
				return NULL;
			if (!root->eow && create_on_miss)	/* insert mode then set the end of word */
				root->eow = 1;
			break;
		}

		if (c < 'a' || c > 'y') {	/* illegal character */
			++key;
			continue;
		}
		
		idx = c - 'a';
		if (!root->next[idx]) {		/* the char doesn't exist */
			if (!create_on_miss)
				return NULL;
			root->next[idx] = trie_node_new();	/* create if it is insert mode */
		}

		root = root->next[idx];
		++key;
	}

	return root;
}

void trie_add_node(struct trie_node *root, const char *key)
{
	printf("********* Add key <%10s> to trie *********\n", key);
	trie_insert(root, key);
	trie_print(root, 1);
	printf("********* Add key <%10s> finish  *********\n", key);
}

void trie_destroy(struct trie_node *root)
{
	int i;

	if (!root)
		return;

	for (i = 0; i < strlen(chr_legal); i++) {
		if (root->next[i]) {
			printf("destroy: %p: %c\n", root->next[i], chr_legal[i]);
			trie_destroy(root->next[i]);
		}
	}

	free(root);
}

int main(void)
{
	char keys[][8] = {"the", "a", "there", "answer",
					  "any", "by", "bye", "their"};

	char output[][20] = {"Exist", "Non-Exist"};

	struct trie_node *root = trie_node_new();

	int i;
	for (i = 0; i < 8; i++)
		trie_add_node(root, keys[i]);

	printf("%s --- %s\n", "the",   output[trie_search(root, "the")   == NULL]);
	printf("%s --- %s\n", "these", output[trie_search(root, "these") == NULL]);
	printf("%s --- %s\n", "their", output[trie_search(root, "their") == NULL]);
	printf("%s --- %s\n", "thaw",  output[trie_search(root, "thaw")  == NULL]);

	trie_destroy(root);

	return 0;
}
