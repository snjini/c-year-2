#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{


if(argv[2] != 0) {
printf("ERROR: Wrong number of arguments. One required.\n");
return -1;
}

    int number = atoi(argv[1]);

if((number%2) == 0) {
printf("ERROR: Bad argument. Height must be positive odd integer.\n");
return -1;
}


    int i, k, count = 1;
 
    count = (number/2);
    for (k = 1; k <= (number/2)+1; k++)
    {
        for (i = 1; i <= count; i++)
            printf(" ");
        count--;
        for (i = 1; i <= 2* k-1; i++)
            printf("*");
        printf("\n");
     }


count = 1;
     for (k = 1; k <= (number/2); k++)
     {
         for (i = 1; i <= count; i++)
             printf(" ");
         count++;
         for (i = 1 ; i <= number-2*k; i++)
             printf("*");
         printf("\n");
      }
 
    return 0;
}
