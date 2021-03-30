#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Copy(char *str,const char *arg, long length){
       
        char *arg_1 =(char*)arg;
        for (long i = 0; i < length; i++)
                str[i] = arg_1[i];
}

int Gcd(int a, int b){
        
        a = (int)labs(a);
        b = (int)labs(b);
        if (b == 0)
                return (int)labs(a);
        return Gcd(b, a % b);
}

void Period_Prefix(long *P, long length, char *str){
        int j = 0,
        position = 1,
        flag;
        
        for (int i = 0; i < length; i++) {
                
                flag = 0;
                
                if (P[i] != 0)
                        j = Gcd(position, (int)P[i]);
                
                for (int k = 0; k + j < position; k++)
                        if (str[k] != str[k+j])
                                flag = 1;
                
                if  ((flag == 0) && (j != 0))
                        printf("%d %d\n", position, position/j);
                
                position++;
        }
}

void Prefix(char *s, long *P, long length){
        P[0] = 0;
        long t = 0, i = 1;
        while (i < length){
                while( (t > 0) && (s[t] != s[i]) )
                        t = P[t-1];
                if (s[t] == s[i])
                        t++;
                P[i] = t;
                i++;
        }
}


int main(int argc, const char * argv[]) {
        
        long length = strlen(argv[1]);
        char str[100] = { '\0' };
        Copy (str, argv[1], length);
        
        long P[length];
        
        Prefix(str, P, length);
        
        Period_Prefix(P, length, str);
        
    return 0;
}
