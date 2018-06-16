
#include <stdio.h>

struct semaphore {
	int					lock;
	unsigned int		count;
};


#define __SEMAPHORE_INITIALIZER(name, n)					\
{															\
	.lock		= 0,										\
	.count		= n,										\
}

#define lockdep_init_map(lock, name, key, sub) \
		do { (void)(name); (void)(key); } while (0)

static inline void sema_init(struct semaphore *sem, int val)
{
	static int __key;
	printf("key is @%p\n", &__key);
	*sem = (struct semaphore) __SEMAPHORE_INITIALIZER(*sem, val);
	//lockdep_init_map(&sem->lock, "semaphore->lock", &__key, 0);
}


int main(void)
{
	struct semaphore sem1, sem2;
	sema_init(&sem1, 1);
	sema_init(&sem2, 2);

	return 0;
}

