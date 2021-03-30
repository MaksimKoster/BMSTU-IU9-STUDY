#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int Max(int a, int b){
	if (a < b)
		return b;
	else
		return a;
}

int Query(int *Tree, int l, int r, int a, int b, int i){
	if ((l == a) && (r == b))
		return Tree[i];
	else{
		int m =floor((a + b)/2);
		if (r <= m)
			return Query(Tree, l, r, a, m, 2*i+1);
		else{
			if (l > m)
				return Query(Tree, l, r, m+1, b, 2*i+2);
			else
				return Max(Query(Tree, l, m, a, m, 2*i+1),
					   Query(Tree, m+1, r, m+1, b, 2*i+2));
		}
	}
}

void Update(int v, int a, int b, int i, int value, int *Tree){
	if (a == b)
		Tree[v] = value;
	else {
		int m = floor((a + b) / 2);
		if (i <= m)
			Update(v*2+1, a, m, i, value, Tree);
		else
			Update(v*2+2, m+1, b, i, value, Tree);
		Tree[v] = Max(Tree[v*2+1], Tree[v*2+2]);
	}
}

void Build (int *arr, int a, int b, int i, int *Tree){
	if (a == b)
		Tree[i] = arr[a];
	else{
		int m = floor((a+b)/2);
		Build(arr, a, m, 2*i + 1, Tree);
		Build(arr, m + 1, b, 2*i + 2, Tree);
		Tree[i] = Max(Tree[2*i+1], Tree[2*i + 2]);
	}
}

int SegmentTree_Query(int *Tree, int n, int l, int r){
	return Query(Tree, l, r, 0, n-1, 0);
}

void SegmentTree_Update(int b, int i, int value, int *Tree){
	Update (0, 0, b, i, value, Tree);
}

void SeqmentTree_Build(int *arr, int *Tree, int length){
	Build(arr, 0, length - 1,  0, Tree);
}

int main(int argc, const char * argv[]) {
	int length, m, arg_1, arg_2;
	char string [4];
	char UPD [4] = "UPD";
	
	scanf("%d", &length);
	int *arr=(int*)malloc(length*sizeof(int));
	for (int i = 0; i < length; i++)
		scanf("%d",&arr[i]);
	
	int *Tree=(int*)malloc((4 * length)*sizeof(int));
	SeqmentTree_Build(arr,Tree, length);
	free(arr);
	
	scanf("%d", &m);
	int answer[m];
	int count = 0;
	for (int i = 0; i < m; i++){
		scanf("%s %d %d", string, &arg_1, &arg_2);
		if (strcmp(string, UPD) == 0)
			SegmentTree_Update(length-1, arg_1, arg_2, Tree);
		
		else{
			answer[count] = SegmentTree_Query(Tree, length, arg_1, arg_2);
			count++;
		}
	}
	free(Tree);
	
	for (int j = 0; j < count; j++)
		printf("%d\n", answer[j]);
    return 0;
}
