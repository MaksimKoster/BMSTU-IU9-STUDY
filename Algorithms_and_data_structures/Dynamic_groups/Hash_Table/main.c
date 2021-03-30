#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem {
	struct Elem *next;
	int key, value;
}Elem;

int h (int i, int m){
	return i % m;
}

Elem *ListSearch(Elem *L, int k){
	Elem *X = L;
	while (X != NULL && X->key != k) {
		X = X->next;
	}
	return X;
}

int Lookup(Elem **T, int key, int m){
	Elem *P = ListSearch(T[h(key, m)], key);
	if (P == NULL) return 0;
	return P->value;
}

Elem *InsertBeforeHead(Elem *L,int key, int value){
	Elem *X = malloc(sizeof(Elem));
	X->key = key;
	X->value = value;
	X->next = L;
	L = X;
	return L;
}

void Insert(Elem **T, int key, int value,int  m){
	int i = h(key, m);
	T[i] = InsertBeforeHead(T[i], key, value);
}

void Delete(Elem *T){
	while (T != NULL) {
		Elem *Delete = T;
		T = Delete->next;
		free(Delete);
	}
}

int main(int argc, const char * argv[]) {
	int n, m, value, key;
	char command[6];
	scanf("%d\n%d", &n ,&m);
	
	Elem **Table = malloc(m * sizeof(Elem *));
	for (int i = 0; i < m; i++)
		Table[i] = NULL;
	
	int count = 0;
	int answer[n];
	
	for (int i = 0; i < n; i++){
		scanf("%s", command);
		
		if(strcmp(command, "ASSIGN") == 0){
			scanf("%d%d", &key,&value);
			Insert(Table, key, value, m);
		}
		if(strcmp(command, "AT") == 0){
			scanf("%d", &key);
			answer[count] = Lookup(Table, key, m);
			count++;
		}
	}
	
	for (int i = 0; i < count; i++)
		printf("%d\n", answer[i]);
	
	for (int i = 0; i < m; i++)
		Delete(Table[i]);
	free(Table);
    return 0;
}

