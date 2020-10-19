#include <stdio.h>
int main(int argc, const char * argv[]) {
	int m, n, column_number = 0, element,position_i= 0, position_j = 0;
	scanf("%d%d", &m, &n);
	if ((m == 1) && (n == 1)){
		scanf("%d", &element);
		printf("%d %d", position_j, position_i);
	}
	else{
		int start_m = m;
		int min_elements_string [n];
		int max_elements_colums [m];
		for (int i = 0; i < n; ++i)
			min_elements_string[i] = 2147483647;
		for (int i = 0; i < m; ++i)
			max_elements_colums[i] = -2147483648;
		while (m > 0){
			for (int j = column_number; j < column_number + 1; ++j){
				for (int i = 0; i < n; i++){
					scanf("%d", &element);
					if (element < min_elements_string[i]){
						min_elements_string[i] = element;
					}
					if (element > max_elements_colums[j]){
						max_elements_colums[j] = element;
					}
				}
			}
			--m;
			++column_number;
		}
		int max_min = min_elements_string[0];
		int min_max = max_elements_colums[0];
		for (int i =0; i < n; i++){
			if (min_elements_string[i] > max_min){
				max_min = min_elements_string[i];
				position_i = i;
			}
		}
		for (int j = 0; j < start_m; j++){
			if(max_elements_colums[j] < min_max){
				min_max = max_elements_colums[j];
				position_j = j;
			}
		}
		if ((min_max == max_min) && (min_elements_string[0] != max_elements_colums[0]))
			printf("%d %d\n", position_j, position_i);
		else
			printf("none\n");
	}
	return 0;
}
