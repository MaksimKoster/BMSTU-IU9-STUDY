#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {
	long k,
	count;
	char value[10];
	struct Tree *parent;
	struct Tree *left;
	struct Tree *right;
} Tree;

int EmptyTree(Tree *T){
	if (!T)
		return 1;
	else
		return 0;
}

Tree *Minimum(Tree *T){
	if (EmptyTree(T))
		return NULL;
	Tree *X = T;
	while (X->left != NULL){
		X->count--;
		X = X->left;
	}
	return X;
}

Tree *Succ(Tree *X){
	if (X->right != NULL){
		return Minimum(X->right);
	}
	Tree *Y = X->parent;
	while (Y != NULL && X == Y->right) {
		X = Y;
		Y = Y->parent;
	}
	return Y;
}

Tree *Descend(Tree *T, long k, int flag){
	Tree *X = T;
	while (X != NULL && X->k != k) {
		if (flag == 1)
			X->count--;
		if (k < X->k)
			X = X->left;
		else
			X = X->right;
	}
	return X;
}

char *Lookup(Tree *T, long k){
	Tree *X = Descend(T, k, 0);
	return X->value;
}

void Copy(char *a, char *b){
	for (int i = 0; i < 10; i++){
		a[i] = b[i];
	}
}

Tree *Insert(Tree *T, long k, char *v){
	Tree *Y;
	Y = malloc(sizeof(Tree));
	Y->k = k;
	Y->count = 0;
	Copy(Y->value, v);
	Y->parent = Y->left = Y->right = NULL;
	
	if (T == NULL)
		T = Y;
	else {
		Tree *X = T;
		while (1) {
			X->count++;
			if (k < X->k) {
				if (X->left == NULL) {
					X->left = Y;
					Y->parent = X;
					break;
				}
				X = X->left;
			}
			else {
				if (X->right == NULL) {
					X->right = Y;
					Y->parent = X;
					break;
				}
				X = X->right;
			}
		}
	}
	return T;
}

Tree *ReplaceNode(Tree *T, Tree *X, Tree *Y){
	if (X == T){
		T = Y;
		if (Y != NULL){
			Y->parent = NULL;
		}
	}
	else{
		Tree *P = X->parent;
		if (Y != NULL) {
			Y->parent = P;
		}
		if (P->left == X) {
			P->left = Y;
		}
		else {
			P->right = Y;
		}
	}
    return T;
}

Tree *Delete(Tree *T, long k) {
	Tree *X = Descend(T, k, 1);
	if (X->left == NULL && X->right == NULL){
		T = ReplaceNode(T, X, NULL);
	}
	else if (X->left == NULL){
		T = ReplaceNode(T, X, X->right);
	}
	else if (X->right == NULL){
		T = ReplaceNode(T, X, X->left);
	}
	else {
		Tree *Y = Succ(X);
		T = ReplaceNode(T, Y, Y->right);
		X->left->parent = Y;
		Y->left = X->left;
		if (X->right != NULL) {
			X->right->parent = Y;
		}
		Y->right = X->right;
		Y->count = X->count-1;
		T = ReplaceNode(T, X, Y);
	}
    free(X);
    return T;
}

void DeleteTree(Tree *T){
	if (!EmptyTree(T)) {
		DeleteTree(T->left);
		DeleteTree(T->right);
		free(T);
	}
}

char *SearchRank(Tree *T, long n) {
	Tree *X = T;
	while(X != NULL){
		if(X->left != NULL){
			if(X->left->count+1 > n)
				X = X->left;
			else{
				if(X->left->count+1 < n){
					n -= X->left->count + 2;
					X = X->right;
				}
				else{
					return X->value;
				}
			}
		}
		else{
			if(n != 0){
				n--;
				X = X->right;
			}
			else{
				return X->value;
			}
		}
	}
	return X->value;
}

int main(int args, char **argv){
	Tree *T = NULL;
	long number_com, K, i;
	char word[10], command[6];
	scanf("%ld", &number_com);
	
	for (i = 0; i < number_com; i++) {
		scanf("%s", command);
		
		if (strcmp(command, "INSERT") == 0){
			scanf("%ld%s", &K, word);
			T = Insert(T, K, word);
		}
		if (strcmp(command, "LOOKUP") == 0){
			scanf("%ld", &K);
			char *answer = Lookup(T, K);
			printf("%s\n", answer);
		}
		if (strcmp(command, "DELETE") == 0){
			scanf("%ld", &K);
			T = Delete(T, K);
		}
		if (strcmp(command, "SEARCH") == 0){
			scanf("%ld", &K);
			char *answer = SearchRank(T, K);
			printf("%s\n", answer);
		}
	}
	DeleteTree(T);
	return 0;
}

