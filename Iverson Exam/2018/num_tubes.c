#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Correct usage: ./num_tubes (n) (k)\n");
    }
    else
    {
        int tubes = atoi(argv[1]);
        int k = atoi(argv[2]);
        int used = 0;
        
        while (tubes >= k)
        {
            tubes -= k;
            used += k;
            tubes++;
        }
        
        int total = tubes + used;
        
        printf("%i\n", total);
    }
}