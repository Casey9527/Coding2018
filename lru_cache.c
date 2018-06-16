/*

cache: page number <-> page frame address (physical)

 */
#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE	5
#define uint32_t unsigned int

struct page {
	int num;
	uint32_t addr;
	struct page *next;
};

struct cache {
	int size;
	int len;
	struct page *head;
};

struct page * page_init(int page_num)
{
	struct page *p;

	p = malloc(1 * sizeof(struct page));
	if (!p) {
		printf("failed to allocate page %d\n", page_num);
		return NULL;
	}

	p->num = page_num;
	p->addr = 0;
	p->next = NULL;

	printf("Init page #%d\n", p->num);
	return p;
}

struct cache * cache_init(int size)
{
	struct cache *c;

	c = malloc(1 * sizeof(struct cache));
	if (!c) {
		printf("failed to allocate cache with size %d\n", size);
	}

	c->size = size;
	c->len = 0;
	c->head = NULL;

	return c;
}

void cache_free(struct cache *cash)
{
	struct page *p;
	struct page *tmp;
	int i;

	if (!cash)
		return;

	p = cash->head;
	while (p) {
		tmp = p;
		p = p->next;
		printf("free page #%d\n", tmp->num);
		free(tmp);
	}
	
	free(cash);
	printf("cache is freed\n");
}

/*
 * insert page reference into cache
 */
void cache_insert_page(struct cache *cash, struct page *p)
{
	struct page *cur;

	if (!cash->head) {
		cash->head = p;
		cash->len++;
		return;
	}

	cur = cash->head;
	while (cur->next)
		cur = cur->next;
	cur->next = p;

	if (cash->len == cash->size) {	/* full. evict */
		struct page *victim;
		victim = cash->head;
		cash->head = victim->next;
		printf("free page #%d\n", victim->num);
		free(victim);
	} else {
		cash->len++;
	}
}

/*
 * lookup page reference from cache
 * return page address if found. Otherwise return NULL
 */
uint32_t cache_lookup_page(struct cache *cash, int page_num)
{
	uint32_t addr;
	struct page *tmp;
	struct page **pprev;
	struct page *cur;

	pprev = &cash->head;
	cur = cash->head;

	while (cur) {
		if (cur->num == page_num) {
			addr = cur->addr;
			break;
		}
		pprev = &cur->next;
		cur = cur->next;
	}

	if (!cur) {
		printf("page not in cache\n");
		return 0;
	}

	if (!cur->next) {
		return addr;
	}

	*pprev = cur->next;

	/* reorder */
	tmp = cur;

	while (tmp->next)
		tmp = tmp->next;

	tmp->next = cur;
	cur->next = NULL;

	return addr;
}

void cache_print_pages(struct cache *cash)
{
	struct page *p;
	p = cash->head;

	printf("len: %d, lru to mru: ", cash->len);
	while (p) {
		printf("%d ", p->num);
		p = p->next;
	}

	printf("\n");
}

uint32_t get_page_from_memory(int page_num)
{
	return page_num | 0x4fff0000;
}

uint32_t get_page_address_from_cache(struct cache *cash, int page_num)
{
	int addr;

	if (!(addr = cache_lookup_page(cash, page_num))) {	/* cache miss */
		struct page *p = page_init(page_num);
		if (!p)
			return 0;

		addr = get_page_from_memory(page_num);		/* To imitate this we just use malloc to get an adress */
		p->addr = addr;
		cache_insert_page(cash, p);	/* insert a page and reorder it */
	}

	return addr;
}

int main(void)
{
	char cmd;
	int n;
	struct cache *cash;
	uint32_t addr;

	cash = cache_init(CACHE_SIZE);
	if (!cash)
		return -1;

	while(1) {
		printf("Input: ");
		scanf(" %c", &cmd);	// use the space to match the newline left in buffer
		switch (cmd) {
			case 'a':
				printf("Num: ");
				scanf(" %d", &n);
				addr = get_page_address_from_cache(cash, n);
				printf("addr: 0x%x\n", addr);
				break;
			case 'p' :
				cache_print_pages(cash);
				break;
			case 'q' :
				goto end;
		}
	}

end:
	cache_free(cash);
	return 0;
}








