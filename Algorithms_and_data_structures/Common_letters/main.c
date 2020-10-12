#include <stdio.h>

int main(int argc, const char * argv[]) {
       char a=0;
       unsigned short arr[52] = {0};
       scanf("%c", &a);
        while (a!=32){
                if (a<91 && a>64)
                       arr[a-65]=1;
                else
                        arr[a-71]=1;
                scanf("%c", &a);
        }
        scanf("%c", &a);
        while (a!=10){
                if ((a<91 && a>64) && (arr[a-65]==1))
                        arr[a-65]=2;
                if ((a < 123 && a > 96) && (arr[a-71]==1))
                        arr[a-71] =2;
                scanf("%c", &a);
        }
        for(int i =0; i < 26; ++i)
                if(arr[i] == 2)
                        printf("%c",i+65);
        for(int i = 26; i < 52; i++)
                if(arr[i]==2)
                        printf("%c",i+71);
        printf("\n");
    return 0;
}
