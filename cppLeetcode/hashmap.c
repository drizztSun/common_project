#include <stdlib.h>

typedef size_t hash_func(const void * key);
typedef size_t equal_func(const void * key1, const void * key2);

struct node{
	void* key;
	void* data;
	struct node* next;
};

struct ht_t {
	size_t bucketSize;
	struct node** bucket;
	hash_func* hash;
	equal_func* equal;
};

struct ht_t* ht_create(size_t size, hash_func* hash, equal_func* equal) {
	struct ht_t* ht = (struct ht_t*)malloc(sizeof(struct ht_t));

	ht->hash = hash;
	ht->equal = equal;
	ht->bucket = (struct node**) malloc(sizeof(struct node*) * size);
	return ht;
}

void ht_add(struct ht_t* ht, void* key, void* data) {
	size_t hashRes = ht->hash(key);
	size_t index = hashRes % ht->bucketSize;

	struct node* n = (struct node*) malloc(sizeof(struct node));
	n->key = key;
	n->data = data;

	struct ndoe* tmp = ht->bucket[index];
	ht->bucket[index] = n;
	n->next = tmp;
} 

size_t ht_find(struct ht_t* ht, void* key) {
	size_t hashRes = ht->hash(key);
	size_t index = hashRes % ht->bucketSize;
	return ht->equal(key, ht->bucket[index]);
}

void ht_remove(struct ht_t* ht, void* key) {
	size_t hashRes = ht->hash(key);
	size_t index = hashRes % ht->bucketSize;

	struct node* p = ht->bucket[index];
	ht->bucket[index] = p->next;
	free(p);
}

void* ht_search(struct ht_t* ht, void* key) {
	size_t hashRes = ht->hash(key);
	size_t index = hashRes % ht->bucketSize;

	struct node* p = ht->bucket[index];
	while (p != 0) {
		if (ht->equal(key, p->key)) {
			return p->data;
		}
		p = p->next;
	}

	return 0;
}

size_t ht_destroy(struct ht_t* ht) {

	for (size_t i = 0; i < ht->bucketSize; i++) {
		struct node* p = ht->bucket[i];
		while (p != 0) {
			struct node* next = p->next;
			free(p);
			p = next;
		}
	}

	free(ht->bucket);
	free(ht);
}

size_t hash_integer(const void* key) {
	return *(int*)key;
}

size_t hash_equal(const void* key1, const void* key2) {
	return *(int*)key1 == *(int*)key2;
}

struct student {
	int no;
	char* name;
};

void test_hashtable() {

	struct ht_t * ht = ht_create(1000, hash_integer, hash_equal);

	struct student tom;
	tom.no = 0, tom.name = "Tom";

	struct student peter;
	peter.no = 1, peter.name = "Peter";

	ht_add(ht, &tom.no, &tom.name);
	ht_add(ht, &peter.no, &peter.name);

	if (ht_find(ht, &tom.no) != 0) {
		printf("We find one like tom\n");
	}

	if (ht_find(ht, 200) != 0) {
		printf("We didn't find any one is 200");
	}

	if (ht_search(ht, tom.no)) {
		printf("We find Tom definately");
	}


	ht_remove(ht, &tom.no);

	struct student lucy;
	lucy.no = 3, lucy.name = "lucy";
	ht_add(ht, &lucy.no, &lucy.name);

	ht_destroy(ht);
}
