#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include "Header.h"



struct kv* kv_cr(char* keyf, void* valuef, char* typef, size_t sizef) { //создание keyvalue
	struct kv* keyvalue = malloc(sizeof(struct kv));
	keyvalue->key = strdup(keyf);
	keyvalue->value = malloc(sizef);
	memcpy(keyvalue->value, valuef, sizef);
	keyvalue->type = strdup(typef);
	keyvalue->size = sizef;
	return keyvalue;
}

struct kv* kv_copy(struct kv* kv) { //  копирует полученные данные
	return kv_cr(kv->key, kv->value, kv->type, kv->size);
}

bool kv_sravni(struct kv* kv1, struct kv* kv2) { //поиск одинаковых значений = сравнение полученных данных
	return !strcmp(kv1->key, kv2->key);
}

void kv_destruct(struct kv* keyvalue) { // делает пустыми во всех ф-ях
	free(keyvalue->key);
	free(keyvalue->value);
	free(keyvalue->type);
	free(keyvalue);
}

struct dict* dict_cr() { //создание словаря
	struct dict* dictionary = malloc(sizeof(struct dict));
	dictionary->n = 0;
	dictionary->arr = NULL;
	return dictionary;
}

void dict_add(struct dict* dictionary, struct kv* keyvalue) { //ok
	struct keyvalue* cur;
	cur = kv_copy(keyvalue);
	if (dict_search2(dictionary, keyvalue->key) == NULL) {
		if (dictionary->n == 0)
		{
			dictionary->arr = malloc(sizeof(struct keyvalue*));
			*(dictionary->arr) = cur;
			dictionary->n++;
			return;
		}
		else {
			dictionary->arr = realloc(dictionary->arr, (dictionary->n + 1) * sizeof(struct kv*));
			*(dictionary->arr + dictionary->n) = cur;
			dictionary->n++;
			return;
		}
	}
	else
	{ 
		struct kv* kv_searched = dict_search(dictionary, keyvalue->key);
		kv_destruct(kv_searched);
		kv_searched = kv_copy(keyvalue);
	}
}

void dict_print(struct dict* dictionary) { //oк
	if (dictionary->n == 0) {
		printf("Словарь пуст\n");
		return;
	}
	printf("Ключ:\t\tЗначение:\n");
	for (int i = 0; i < dictionary->n; i++) {
		if (strcmp(dictionary->arr[i]->type, "int") == 0) {
			printf("%s\t\t%d\n", (char*)(*(dictionary->arr + i))->key, *(int*)(*(dictionary->arr + i))->value);
		}
		else if (strcmp(dictionary->arr[i]->type, "float") == 0) {
			printf("%s\t\t%f\n", (char*)(*(dictionary->arr + i))->key, *(float*)(*(dictionary->arr + i))->value);
		}
		else if (strcmp(dictionary->arr[i]->type, "char") == 0) {
			printf("%s\t\t%s\n", (char*)(*(dictionary->arr + i))->key, *(char**)(*(dictionary->arr + i))->value);
		}
		else printf("%s\t\t%p\n", (char*)(*(dictionary->arr + i))->key, (*(dictionary->arr + i))->value);
	}
}

struct kv* dict_search(struct dict* dictionary, char* keyf) { //возвращает структуру
	for (int i = 0; i < dictionary->n; i++) {
		if (strcmp(dictionary->arr[i]->key, keyf) == 0) {
			return (&dictionary->arr[i]);
		}
	}
	return NULL;
}

void* dict_search2(struct dict* dictionary, char* keyf) { //возвращает значение
	for (int i = 0; i < dictionary->n; i++) {
		if (strcmp(dictionary->arr[i]->key, keyf) == 0) {
			return dictionary->arr[i]->value;
		}
	}
	return NULL;
}

void dict_destruct(struct dict* dictionary) { //ok
	for (int i = 0; i < dictionary->n; i++) {
		kv_destruct(dictionary->arr[i]);
	}
	dictionary->n = 0;
	free(dictionary->arr);
	free(dictionary);
}

void dict_elem_destruct(struct dict* dictionary, char* keyf) { 
	for (int i = 0; i < dictionary->n; i++) {
		if (strcmp(dictionary->arr[i]->key, keyf) == 0) { // == 0 если одинаковые
			if (i != dictionary->n - 1) { //если не последний
				dictionary->arr[i] = kv_copy(dictionary->arr[dictionary->n - 1]); //записываем в удаленное последнее значение
			}
			kv_destruct(dictionary->arr[dictionary->n - 1]);
			dictionary->arr = realloc(dictionary->arr, (dictionary->n - 1) * sizeof(struct kv));
			dictionary->n--;
		}
	}
}
