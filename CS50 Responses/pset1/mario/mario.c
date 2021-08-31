#include <stdio.h>
#include <cs50.h>

int main(void){

    int Height;
    char Space = ' ', Hash = '#';
    string gap = "  ";

    do{
        Height = get_int("Height: ");
    }
    while(Height < 1 || Height > 8);

    for(int i = 1; i <= Height; i++){
        for(int a = 1; a <= (Height-i); a++){
            printf("%c", Space);
        }
        for(int b = 1; b <= i; b++){
            printf("%c", Hash);
        }
        printf("%s", gap);
        for(int b = 1; b <= i; b++){
            printf("%c", Hash);
        }
        printf("\n");
    }
}