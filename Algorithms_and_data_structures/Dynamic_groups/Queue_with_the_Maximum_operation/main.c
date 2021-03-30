#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Que_With_Max {
	long **stack;
	long top1;
	long top2;
	long cap;
} a;

long max_compare(long a, long b){
	if (a > b)
		return a;
	else
		return b;
}

long StackEmpty1(struct Que_With_Max* a){
	if (a->top1 == 0)
		return 1;
	else
		return 0;
}

long StackEmpty2(struct Que_With_Max* a){
	if (a->top2 == a->cap - 1)
		return 1;
	else
		return 0;
}

void Push1(struct Que_With_Max *a, long x){
	a->stack[a->top1][0] = x;
	if (StackEmpty1(a))
		a->stack[a->top1][1] = x;
	else
		a->stack[a->top1][1] = max_compare(x, a->stack[a->top1 - 1][1]);
	a->top1++;
}


void Push2(struct Que_With_Max *a, long x){
	a->stack[a->top2][0] = x;
	if (StackEmpty2(a))
		a->stack[a->top2][1] = x;
	else
		a->stack[a->top2][1] = max_compare(x, a->stack[a->top2 + 1][1]);
	a->top2--;
}

long Pop1(struct Que_With_Max *a){
	a->top1--;
	return a->stack[a->top1][0];
}

long Pop2(struct Que_With_Max *a){
	a->top2++;
	return a->stack[a->top2][0];
}

void Empty(struct Que_With_Max *a){
	if (StackEmpty1(a) * StackEmpty2(a))
		printf("true\n");
	else
		printf("false\n");
}

void Enq(struct Que_With_Max *a, long x){
	Push1(a, x);
}

void Deq(struct Que_With_Max *a){
	if (StackEmpty2(a)) {
		while (!StackEmpty1(a))
			Push2(a, Pop1(a));
	}
	printf("%ld\n", Pop2(a));
}

void Max(struct Que_With_Max* a){
	if (StackEmpty1(a)){
		printf("%ld\n", a->stack[a->top2 + 1][1]);
		return;
	}
	if (StackEmpty2(a)){
		printf("%ld\n", a->stack[a->top1 - 1][1]);
		return;
	}
	printf ("%ld\n", max_compare(a->stack[a->top2 + 1][1], a->stack[a->top1 - 1][1]));
}

void First_initialize(int n){
	a.stack = (long**)malloc(n * sizeof(long*));
	for (int i = 0; i < n; i++)
		a.stack[i] = (long*)malloc(2 * sizeof(long));
		
	a.top1 = 0;
	a.top2 = n - 1;
	a.cap = n;
};

int main(int argc, const char * argv[]){
	
	long num_commands, x;
	char command[7];
	scanf("%ld", &num_commands);
	
	First_initialize((int)num_commands);
	
	for(int i = 0; i < num_commands; i++) {
		
		scanf("%s", command);
		
		if (strcmp(command,"EMPTY") == 0)
			Empty(&a);
		
		if (strcmp(command,"ENQ") == 0){
			scanf("%ld", &x);
			Enq(&a, x);
		}
		if (strcmp(command,"DEQ") == 0)
			Deq(&a);
		
		if (strcmp(command, "MAX") == 0)
			Max(&a);
	}
	for (int i = 0; i < num_commands; i++)
		free(a.stack[i]);
	free(a.stack);
	return 0;
}
