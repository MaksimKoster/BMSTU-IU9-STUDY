#include <stdio.h>
int main(int argc, const char * argv[]) {
		int a1, a2, search = 0, n;
		scanf("%d\n", &n);
		scanf("%d", &a1);
		for (int i = 0; i < n-1; i++){
				scanf("%d", &a2);
				if (a2 != a1){
						if (search == 0)
								printf("0 ");
						else
								printf("%d ", a1);
				}
				else{
						if (search == 0){
								printf("1 ");
								search = 1;
						}
						else
								printf("%d ", a1);
				}
				a1 = a2;
		}
		if (a1 == 0)
				printf("1 ");
		else{
				if ((a1 == 1) && (search == 0))
						printf("0 1");
				else
						printf("%d", a1);
		}
		printf("\n");
		return 0;
}
