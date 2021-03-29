#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int args, char **argv){
        if (args != 4){
                printf("Usage: frame <height> <width> <text>");
                return 0;
        }
        
        int height = atoi(argv[1]),height_changeable;
        int width = atoi(argv[2]);
        int center_column = (height / 2) - 1;
        int center_string = (width - ((int)strlen(argv[3]))) / 2;
        
        if ((strlen(argv[3]) > width - 2) || (height <= 2)){
                printf("Error");
                return 0;
        }
        
        for (int i = 0; i < width; i++)                   //Печать первой строки
                printf("*");
        printf("\n");
        
        if (atoi(argv[1]) % 2 == 0)                      //Провека на четность столбцов
                height_changeable = center_column;
        else
                height_changeable = height / 2;
        
        for (int i = 1; i < height_changeable; i++){          //Печать до строки где будет текст
                printf("*");
                for (int i = 1; i < width - 1; i++)
                        printf(" ");
                printf("*\n");
        }
        
        printf("*");                                      //Печать строки с текстом
        for (int i = 1; i < center_string; i++)
                printf(" ");
        printf("%s", argv[3]);
        for (int i = 0; i < width - ((int)strlen(argv[3])) - center_string - 1; i++)
                printf(" ");
        printf("*\n");

    for (int i = height_changeable; i < height - 2; i++){       //Печать строк до последней строки
                printf("*");
                for (int i = 1; i < width - 1; i++)
                        printf(" ");
                printf("*\n");
        }
        
        for (int i = 0; i < width; i++)                   //Печать последней строки
                printf("*");
        printf("\n");
}
