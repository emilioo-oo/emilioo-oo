#pragma once
#include <stdbool.h>
struct kv {
	char* key;
	void* value;
	char* type;
	size_t size;
};

struct dict {
	struct kv** arr;
	int n;
};


struct kv* kv_cr(char* keyf, void* valuef, char* typef, size_t sizef);

struct kv* kv_copy(struct kv* kv);

bool kv_sravni(struct kv* kv1, struct kv* kv2);

void kv_destruct(struct kv* keyvalue);

struct dict* dict_cr();

void dict_add(struct dict* dictionary, struct kv* keyvalue);

void dict_print(struct dict* dictionary);

struct kv* dict_search(struct dict* dictionary, char* keyf);

void* dict_search2(struct dict* dictionary, char* keyf);

void dict_destruct(struct dict* dictionary);

void dict_elem_destruct(struct dict* dictionary, char* keyf);
