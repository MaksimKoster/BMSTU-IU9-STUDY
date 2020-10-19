#include <stdio.h>
int main(int argc, const char * argv[]) {
		int n;
		long a1,a2,arr[2];
		scanf ("%d", &n);
		for (int i =0; i < 2; ++i)
				scanf("%ld", &arr[i]);
		if (n == 1)
				n = 0;
		if (n == 2)
				n = 1;
		while (n > 0){
				scanf("%ld %ld",&a1,&a2);
				if (((arr[0] <= a1) && (a1 < arr[1])&&(arr[1] <a2)))
						arr[1] = a2;
				else{
						if((a1 - arr[1]) == 1)
								arr[1] = a2;
						else{
								if((arr[0] <= a1)&&(a2 <= arr[1])){
										arr[0]=arr[0] + 0;
										arr[1]=arr[1] + 0;
								}
								else{
										printf("%ld %ld\n", arr[0],arr[1]);
										arr[0]=a1;
										arr[1]=a2;
								}
						}
				}
				--n;
		}
		printf("%ld %ld\n", arr[0],arr[1]);
		return 0;
}
