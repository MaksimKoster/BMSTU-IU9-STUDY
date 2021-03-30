#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void FUNCTION_DUP(int *Stack,int Position_Stack){
	Stack[Position_Stack + 1] = Stack[Position_Stack];
}

void FUNCTION_NEG(int *Stack,int Position_Stack){
	Stack[Position_Stack] = -1 * Stack[Position_Stack];
}

void FUNCTION_MIN(int *Stack,int Position_Stack){
	if (Stack[Position_Stack] < Stack[Position_Stack - 1])
		Stack[Position_Stack - 1] = Stack[Position_Stack];
	else
		Stack[Position_Stack] = 0;
}

void FUNCTION_MAX(int *Stack,int Position_Stack){
	if (Stack[Position_Stack] > Stack[Position_Stack - 1])
		Stack[Position_Stack - 1] = Stack[Position_Stack];
	else
		Stack[Position_Stack] = 0;
}

void FUNCTION_DIV(int *Stack,int Position_Stack){
	Stack[Position_Stack - 1] = Stack[Position_Stack] / Stack[Position_Stack - 1];
	Stack[Position_Stack] = 0;
}

void FUNCTION_MUL(int *Stack,int Position_Stack){
	Stack[Position_Stack - 1] = Stack[Position_Stack - 1] * Stack[Position_Stack];
	Stack[Position_Stack] = 0;
}

void FUNCTION_SUB(int *Stack, int Position_Stack){
	Stack[Position_Stack - 1] = Stack[Position_Stack] - Stack[Position_Stack - 1];
	Stack[Position_Stack] = 0;
}

void FUNCTION_ADD(int *Stack, int Position_Stack){
	Stack[Position_Stack - 1] = Stack[Position_Stack - 1] + Stack[Position_Stack];
	Stack[Position_Stack] = 0;
}

void FUNCTION_CONST(int *Stack, int Position_Stack, int x){
	Stack[Position_Stack] = x;
}


int main(int argc, const char * argv[]) {
	int Stack[100001],
	Position_Stack = -1,
	x,
	Count_Commands;
	
	
	char Command [7];
	
	scanf("%d", &Count_Commands);
	
	for(int i = 0; i < Count_Commands; i++){
		
		for (int i = 0; i < 7; i++)
			Command[i] = '\0';
		
		scanf("%s", Command);
		
		if(strcmp(Command, "CONST") == 0){
			scanf("%d", &x);
			Position_Stack++;
			FUNCTION_CONST(Stack, Position_Stack, x);
		}
		
		if(strcmp(Command, "ADD") == 0){
			FUNCTION_ADD(Stack, Position_Stack);
			Position_Stack--;
		}
		
		
		if(strcmp(Command, "SUB") == 0){
			FUNCTION_SUB(Stack, Position_Stack);
			Position_Stack--;
		}
		
		if(strcmp(Command, "MUL") == 0){
			FUNCTION_MUL(Stack, Position_Stack);
			Position_Stack--;
		}
		
		if(strcmp(Command, "DIV") == 0){
			FUNCTION_DIV(Stack, Position_Stack);
			Position_Stack--;
		}
		
		if(strcmp(Command, "MAX") == 0){
			FUNCTION_MAX(Stack, Position_Stack);
			Position_Stack--;

		}
		
		if(strcmp(Command, "MIN") == 0){
			FUNCTION_MIN(Stack, Position_Stack);
			Position_Stack--;

		}
		
		if(strcmp(Command, "NEG") == 0)
			FUNCTION_NEG(Stack, Position_Stack);
		
		if(strcmp(Command, "DUP") == 0){
			FUNCTION_DUP(Stack, Position_Stack);
			Position_Stack++;
		}
		
		if(strcmp(Command, "SWAP") == 0){
			int change = Stack[Position_Stack];
			Stack[Position_Stack] = Stack[Position_Stack - 1];
			Stack[Position_Stack - 1] = change;
		}
	}
	printf("%d\n", Stack[0]);
	return 0;
}
