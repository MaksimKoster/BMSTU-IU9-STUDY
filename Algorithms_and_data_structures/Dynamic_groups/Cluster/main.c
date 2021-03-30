#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    long *heap;
    long cap,
    count;
};

void Swap(struct PriorityQueue *a, long x ,long y){
	a->heap[x] = a->heap[x] + a->heap[y] - (a->heap[y] = a->heap[x]);
}

void Insert(struct PriorityQueue *a, long x){
	long i = a->count;
	if (i == a->cap)
		printf("Error");
	a->count = i + 1;
	a->heap[i] = x;
	while (i > 0 && (a->heap[(i - 1) / 2]) > a->heap[i]){
		Swap(a, (i - 1) / 2, i);
		i = (i - 1) / 2;
	}
}

void Heapify(long i, long n, struct PriorityQueue *a){
	while (1){
		long l = 2 * i + 1,
		r = l + 1,
		j = i;
		
		if (l < n && a->heap[i] > a->heap[l])
			i = l;
		if (r < n && a->heap[i] > a->heap[r])
			i = r;
		if (i == j)
			break;
		Swap(a, i, j);
	}
}

long Extract_Min(struct PriorityQueue *a){
	if (a->count == 0)
		printf("Empty");
	long x = a->heap[0];
	a->count--;
	if (a->count > 0) {
		a->heap[0] = a->heap[a->count];
		Heapify(0, a->count, a);
	}
	return x;
}

void Insert_Right_Time(struct PriorityQueue *a, long t1, long t2){
	long time = Extract_Min(a);
	if (time < t1)
		time += t1 - time + t2;
	else
		time += t2;
	Insert(a, time);
}

int main(int args, char **argv){
	
	long N, M,
	t1, t2;
	scanf("%ld\n%ld", &N, &M);
	
	struct PriorityQueue a;
	a.heap = malloc(N * sizeof(long));
	a.count = 0;
	a.cap = N;
	
	for (long i = 0; i < N; i++){
		scanf("%ld %ld", &t1, &t2);
		Insert(&a, t1 + t2);
	}
	
	for (long i = 0; i < M - N; i++){
		scanf("%ld %ld", &t1, &t2);
		Insert_Right_Time(&a,t1,t2);
	}
	
	for (int i = 0; i < N - 1; i++){
		Extract_Min(&a);
	}
	
	printf("%ld\n", Extract_Min(&a));
	free(a.heap);
    return 0;
}
