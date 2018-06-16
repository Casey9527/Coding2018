
/*
 * https://www.rosettacode.org/wiki/Inverted_index#C
 */

#include <stdio.h>
#include <stdlib.h>

char chr_legal[] = "abcdefghijklmnopqrstuvwxyz0123456789_-./";
int  chr_idx[256] = {0};
char idx_chr[256] = {0};

#define FNAME 0
#define USE_ADVANCED_FILE_HANDLING 1

typedef struct trie_t *trie, trie_t;
struct trie_t {
	trie next[sizeof(chr_legal)];	/* next letter; slot 0 is file name */
	int eow;						/* 1 if current trie node is the end of word */
};

trie trie_new()
{
	return calloc(sizeof(trie_t), 1);
}

#define find_word(r, w) trie_trav(r, w, 1)

void print_trie(trie root, int level)
{
	int i;

	if (!root)
		return;

	level++;
	for (i = 0; i < sizeof(chr_legal); i++) {
		if (root->next[i]) {
			printf("level: %d, c: %c\n", level, idx_chr[i]);
			print_trie(root->next[i], level);
		}
	}
}

trie trie_trav(trie root, const char *s, int no_create)
{
	int c;
	while (root) {
		if ((c = s[0]) == '\0') {
			if (!root->eow && no_create) return 0;
			break;
		}

		if (!(c = chr_idx[c])) {
			s++;
			continue;
		}

		if (!root->next[c]) {
			if (no_create) return 0;
			root->next[c] = trie_new();
		}
		root = root->next[c];
		++s;
	}

	return root;
}

/*
 * Complete traversal of whole tree, calling callback at each end of word node,
 * similar method can be used to free nodes, had we wanted to do that.
 */
int trie_all(trie root, char path[], int depth, int (*callback)(char *))
{
	int i;
	if (root->eow && !callback(path)) return 0;
	
	for (i = 1; i < sizeof(chr_legal); i++) {
		if (!root->next[i]) continue;

		path[depth] = idx_chr[i];
		path[depth + 1] = '\0';
		if (!trie_all(root->next[i], path, depth + 1, callback))
			return 0;
	}

	return 1;
}

void add_index(trie root, const char *word, const char *fname)
{
	trie x = trie_trav(root, word, 0);
	x->eow = 1;
	if (!x->next[FNAME])
		x->next[FNAME] = trie_new();
	x = trie_trav(x->next[FNAME], fname, 0);
	x->eow = 1;
//	printf("add_index: word: %s, frame: %s\n", word, fname);
//	print_trie(root, 0);
//	printf("add_index end----------------------------\n");
}

int print_path(char *path)
{
	printf(" %s", path);
	return 1;
}

#ifdef USE_ADVANCED_FILE_HANDLING
void read_file(trie root, const char *fname) {
	char cmd[1024];
	char word[1024];
	sprintf(cmd, "perl -p -e 'while(/(\\w+)/g) {print lc($1),\"\\n\"}' %s", fname);
	FILE *in = popen(cmd, "r");
	while (!feof(in)) {
		fscanf(in, "%1000s", word);
		add_index(root, word, fname);
	}
	pclose(in);
}
#endif

/*  pretend we parsed text files and got lower cased words: dealing     *
 *  with text file is a whole other animal and would make code too long */
const char *files[] = { "f1.txt", "source/f2.txt", "other_file" };
const char *text[][5] ={{ "it", "is", "what", "it", "is" },
						{ "what", "is", "it", 0 },
						{ "it", "is", "a", "banana", 0 }};

trie init_tables()
{
	int i, j;
	trie root = trie_new();
	for (i = 0; i < sizeof(chr_legal); i++) {	/* sizeof considers the terminating null */
		chr_idx[(int)chr_legal[i]] = i + 1;
		idx_chr[i + 1] = chr_legal[i];
	}

	idx_chr[0] = '#';

#if USE_ADVANCED_FILE_HANDLING
	read_file(root, "f1.txt");
	read_file(root, "source/f2.txt");
	read_file(root, "other_file");
#else
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 5; j++) {
			if (!text[i][j])	break;
			add_index(root, text[i][j], files[i]);
		}
	}
#endif	/* USE_ADVANCED_FILE_HANDLING */
	return root;
}

void search_index(trie root, const char *word)
{
	char path[1024];
	printf("Search for \"%s\": ", word);
	trie found = find_word(root, word);

	if (!found)	printf("not found\n");
	else {
		trie_all(found->next[FNAME], path, 0, print_path);
		printf("\n");
	}
}

int main()
{
	trie root = init_tables();

//	print_trie(root, 0);

	search_index(root, "what");
	search_index(root, "is");
	search_index(root, "banana");
	search_index(root, "boo");
	return 0;
}
