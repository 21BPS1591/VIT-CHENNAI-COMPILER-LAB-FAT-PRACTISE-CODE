// implement a DFA whereby, it gets the inputs from user such as the number of states, number of input symbols, the input symbols, and the transitions.
#include <stdio.h>
#include <string.h>
typedef struct DFA
{
    int num_states;
    int num_inputs;
    int num_finalstates;
    int transition[10][10];
    int final[10];
    char inputSymbols[10];
} DFA;

int checkSymbol(char ch, DFA d)
{
    for (int i = 0; i < d.num_inputs; i++)
    {
        if (ch == d.inputSymbols[i])
        {
            return i;
        }
    }
    return -1;
}

int checkFinalState(int st, DFA d)
{
    for (int i = 0; i < d.num_finalstates; i++)
    {
        if (st == d.final[i])
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    DFA d;
    printf("\nEnter no of states: ");
    scanf(" %d", &d.num_states);
    printf("\nEnter no of final states: ");
    scanf(" %d", &d.num_finalstates);
    printf("\nEnter no of input symbols: ");
    scanf(" %d", &d.num_inputs);

    for (int i = 0; i < d.num_inputs; i++)
    {
        printf("Enter input symbol no %d : ", i + 1);
        scanf(" %c", &d.inputSymbols[i]);
    }

    for (int i = 0; i < d.num_finalstates; i++)
    {
        printf("Enter final state no %d : ", i + 1);
        scanf(" %d", &d.final[i]);
    }

    printf("\nEnter transitions: ");

    for (int i = 0; i < d.num_states; i++)
    {
        for (int j = 0; j < d.num_inputs; j++)
        {
            printf("\nd(q%d,%c) : ", i, d.inputSymbols[j]);
            scanf(" %d", &d.transition[i][j]);
        }
    }

    for (int i = 0; i < d.num_inputs; i++)
        printf("\t %c", d.inputSymbols[i]);
    printf("\n");
    for (int i = 0; i < d.num_states; i++)
    {
        printf("\nq%d", i);
        for (int j = 0; j < d.num_inputs; j++)
        {
            printf("\t%d", d.transition[i][j]);
        }
        printf("\n");
    }

    char proceed = 'y';
    do
    {
        char string[10];
        printf("\nEnter a string: ");
        scanf("%s", string);
        int current = 0; // current here means current state
        int flag = 1;
        for (int i = 0; i < strlen(string); i++)
        {
            int symPos = checkSymbol(string[i], d);
            if (symPos == -1)
            {
                flag = 0;
                break;
            }
            current = d.transition[current][symPos];
        }
        if (flag == 1 && checkFinalState(current, d) == 1)
        {
            printf("%s is accepted. \n", string);
        }
        else
        {
            printf("%s is not accpeted. \n", string);
        }
        printf("Continue? (y/n): ");
        scanf(" %c", &proceed);
    } while (proceed == 'y');
    return 0;
}