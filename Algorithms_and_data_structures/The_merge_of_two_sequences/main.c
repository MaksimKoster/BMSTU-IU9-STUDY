#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
		int n1, n2, i = 0, j = 0;
		scanf("%d", &n1);
		int *arr_1 = (int*)malloc(n1 * sizeof(int));
		for (int i = 0; i < n1; i++) {
				scanf("%d", &arr_1[i]);
		}
		scanf("%d", &n2);
		int *arr_2= (int*)malloc(n2 * sizeof(int));
		for (int i = 0; i < n2; i++) {
				scanf("%d", &arr_2[i]);
				
		}
		while (i < n1 && j < n2){
				if (arr_1[i] < arr_2[j]){
						printf("%d ", arr_1[i]);
						i++;
				}
				else{
						printf("%d ", arr_2[j]);
						j++;
				}
		}
		while (i < n1){
				printf("%d ", arr_1[i]);
				i++;
		}
		while (j < n2){
				printf("%d ", arr_2[j]);
				j++;
		}
		free(arr_1);
		free(arr_2);
		return 0;
}
