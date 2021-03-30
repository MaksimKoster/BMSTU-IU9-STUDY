#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem {
	struct Elem *next;
	long int key, value;
}Elem;
struct Count {
	long int value;
}Count;

long int h (long int i,long int m){
	return (long int)(i % m);
}

Elem *ListSearch(Elem *L, long int k){
	Elem *X = L;
	while (X != NULL && X->key != k) {
		X = X->next;
	}
	return X;
}

Elem *InsertBeforeHead(Elem *L,long int key,long int value){
	Elem *X = malloc(sizeof(Elem));
	X->key = key;
	X->value = value;
	X->next = L;
	L = X;
	return L;
}

void Insert(Elem **T, long int key,long int value,long int  m){
	long int i = h(key, m);
	T[i] = InsertBeforeHead(T[i], key, value);
}

void Delete(Elem *T, struct Count *Count){
	while (T != NULL) {
		Elem *Delete = T;
		T = Delete->next;
		Count->value += Delete->value;
		free(Delete);
	}
}

int main(int argc, const char * argv[]) {
	long int length, help = 0, elem;
	Elem *Y = NULL;
	scanf("%ld", &length);
	Count.value = 0;
	
	Elem **Table = malloc(length * sizeof(Elem *));
	for (int i = 0; i < length; i++){
		Table[i] = NULL;
		if (i == 0)
			Insert(Table, i,i, 1);
        }
	for(int i = 0; i < length; i++){
		scanf("%ld", &elem);
		help = help ^ elem;
		Y = ListSearch(Table[h(help,length)], help);
		if (Y == NULL)
			Insert(Table, help, 0, length);
		else{
			Count.value += Y->value;
			Y->value++;
		}
	}
	for (int i = 0; i < length; i++)
		Delete(Table[i], &Count);
	printf("%ld\n", Count.value);
	free(Table);
	return 0;
}

