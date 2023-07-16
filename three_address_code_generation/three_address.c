#include <stdio.h>
#include <string.h>

void pm();
void plus();
void div();

int i, ch, j, l, addr = 100;
char ex[10], expp[10], exp1[10], expp2[10], id1[5], op[5], id2[5];

int main()
{
    while (1)
    {
        printf("\n1.assignment\n2.arithmetic\n3.relational\n4.Exit\nEnter the choice:");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("\nEnter the expression with assignment operator:");
            scanf("%s", expp);
            l = strlen(expp);
            expp2[0] = '\0';
            i = 0;
            while (expp[i] != '=')
            {
                i++;
            }
            strncat(expp2, expp, i);
            strrev(expp);
            exp1[0] = '\0';
            strncat(exp1, expp, l - (i + 1));
            strrev(exp1);
            printf("Three address code:\ntemp=%s\n%s=temp\n", exp1, expp2);
            break;

        case 2:
            printf("\nEnter the expression with arithmetic operator:");
            scanf("%s", ex);
            strcpy(expp, ex);
            l = strlen(expp);
            exp1[0] = '\0';
            for (i = 0; i < l; i++)
            {
                if (expp[i] == '+' || expp[i] == '-')
                {
                    if (expp[i + 2] == '/' || expp[i + 2] == '*')
                    {
                        pm();
                        break;
                    }
                    else
                    {
                        plus();
                        break;
                    }
                }
                else if (expp[i] == '/' || expp[i] == '*')
                {
                    div();
                    break;
                }
            }
            break;

        case 3:
            printf("Enter the expression with relational operator\n");
            scanf("%s%s%s", id1, op, id2);
            if (((strcmp(op, "<") == 0) || (strcmp(op, ">") == 0) || (strcmp(op, "<=") == 0) || (strcmp(op, ">=") == 0) || (strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) == 0)
                printf("Expression is error");
            else
            {
                printf("\n%d\tif (%s %s %s) goto %d", addr, id1, op, id2, addr + 3);
                addr++;
                printf("\n%d\t T:=0", addr);
                addr++;
                printf("\n%d\t goto %d", addr, addr + 2);
                addr++;
                printf("\n%d\t T:=1", addr);
            }
            break;

        case 4:
            return 0;
        }
    }
}

void pm()
{
    strrev(expp);
    j = l - i - 1;
    strncat(exp1, expp, j);
    strrev(exp1);
    printf("Three address code:\ntemp=(%s)\ntemp1=(%c%ctemp)\n", exp1, expp[j + 1], expp[j]);
}

void div()
{
    strncat(exp1, expp, i + 2);
    printf("Three address code:\ntemp=(%s)\ntemp1=temp%c%c\n", exp1, expp[i + 2], expp[i + 3]);
}

void plus()
{
    strncat(exp1, expp, i + 2);
    printf("Three address code:\ntemp=(%s)\ntemp1=temp%c%c\n", exp1, expp[i + 2], expp[i + 3]);
}