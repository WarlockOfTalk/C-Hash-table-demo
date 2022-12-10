#include <stdio.h>

int main(void)
{
./    char usr_input = 'n';

    if(usr_input == 'n')
    {
        printf("YES\n");
    }

    while (usr_input != 'y' || usr_input != 'n')
    {
        printf("%c\n", usr_input);
        printf("Invalid selection, please choose y/n\n");
        usr_input = fgetc(stdin);

    }
}