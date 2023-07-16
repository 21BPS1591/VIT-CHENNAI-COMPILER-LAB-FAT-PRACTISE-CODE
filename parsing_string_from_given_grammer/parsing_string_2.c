#include <stdio.h>
#include <string.h>
#include <ctype.h>
char input[100];
int i = 0;
int error;

void S();
void L();
void R();

int main()
{
    printf("Enter the input string: ");
    scanf("%s", input);
    S();
    if (input[i] == '\0' && error == 0)
    {
        printf("The string %s is Accepted\n", input);
    }
    else
    {
        printf("The string %s is Rejected\n", input);
    }
    return 0;
}

void S()
{
    if (isalpha(input[i]))
    {
        i++;
        if (input[i] == '=')
        {
            i++;
            R();
        }
        else
        {
            error = 1;
        }
    }
    else
    {
        L();
        if (input[i] == '=')
        {
            i++;
            R();
        }
        else
        {
            error = 1;
        }
    }
}

void L()
{
    if (input[i] == '*')
    {
        i++;
        R();
    }
    else if (isalpha(input[i]))
    {
        i++;
    }
    else
    {
        error = 1;
    }
}

void R()
{
    L();
}