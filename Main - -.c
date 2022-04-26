#include "Header.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main() {
	setlocale(LC_ALL, "RU");
	char a[] = "abc";
	int b = 777;
	struct kv* kv1 = kv_cr(a, &b, "int", sizeof(int));
	struct kv* copy = kv_copy(kv1);
	printf("%d\n", kv_sravni(kv1, copy));
	copy->key[1] = 'x';
	char e[] = "axc";


	struct dict* dictionary = dict_cr();
	printf("%d\n\n", kv_sravni(kv1, copy));
	dict_print(dictionary);
	dict_add(dictionary, kv1);
	dict_print(dictionary);
	printf("----------------------------------------\n");
	dict_add(dictionary, copy);
	dict_print(dictionary);
	printf("----------------------------------------\n");
	dict_elem_destruct(dictionary, a);
	dict_print(dictionary);
	printf("----------------------------------------\n");
	dict_destruct(dictionary);
	dict_print(dictionary);
	printf("----------------------------------------\n");

	return 0;
}
