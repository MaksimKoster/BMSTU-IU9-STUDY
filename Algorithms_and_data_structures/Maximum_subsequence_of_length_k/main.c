#include <stdio.h>

int main(int argc, const char * argv[]){
	long n, k, delete, add, sum_first = 0, sum_last = 0, position = 0;
	scanf("%ld %ld", &n, &k);
	long  arr[k];
	for (int i = 0; i < k; i++){
		scanf("%ld", &arr[i]);
		sum_first += arr[i];
	}
	sum_last = sum_first;
	for (long i = k; i < n; i++){
		delete = arr[i%k];
        scanf("%ld", &arr[i%k]);
		add = arr[i%k];
        if (sum_last < sum_first - delete + add){
		position = i-k+1;
		sum_last= sum_first - delete + add;
	}
        sum_first = sum_first - delete + add;
		add = 0;
		delete = 0;
    }
    printf("%ld\n", position);
    return 0;
}
