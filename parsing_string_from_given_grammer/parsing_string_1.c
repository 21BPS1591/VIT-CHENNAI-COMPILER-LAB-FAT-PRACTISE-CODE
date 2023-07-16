#include <stdio.h>
#include <string.h>
#include <ctype.h>
char input[100];
int i = 0;
int error;

void E();
void Eds();
void T();
void Tds();
void F();

int main()
{
    printf("Enter the input string: ");
    scanf("%s", input);
    E();
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

void E()
{
    T();
    Eds();
}

void Eds()
{
    if (input[i] == '+')
    {
        i++;
        T();
        Eds();
    }
}

void T()
{
    F();
    Tds();
}

void Tds()
{
    if (input[i] == '*')
    {
        i++;
        F();
        Tds();
    }
}

void F()
{
    if (input[i] == '(')
    {
        i++;
        E();
        if (input[i] == ')')
        {
            i++;
        }
        else
        {
            error = 1;
        }
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
