#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[])
{
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
    int i, flag = 0;
    for (i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}
int isLibFunction(char buffer[])
{
    char libraryfunctions[40][10] = {"printf(", "scanf(", "fgets(", "strlen(", "strcpy(", "strcat(", "strcmp(", "malloc(", "free(", "sqrt(", "rand(", "time(", "toupper(", "tolower(", "isdigit(", "isalpha(", "fopen(", "fclose(", "fscanf(", "fread(", "fwrite(", "fwrite(", "sin(", "cos(", "exp(", "log(", "pow(", "ceil(", "floor(", "memcpy(", "memmove(", "memset(", "memcmp(", "calloc(", "realloc(", "isalnum(", "isblank(", "isspace(", "isupper(", "islower("};
    int i, flag = 0;
    for (i = 0; i < 32; ++i)
    {
        if (strcmp(libraryfunctions[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}
int main()
{
    char ch, buffer[20], operators[] = "+-*/%=", special[] = "&_{}#!|$";
    FILE *fp;
    int i, j = 0, z = 0;
    int isPreprocessor = 0; // Flag to indicate preprocessor directive
    fp = fopen("thisfile.txt", "r");
    if (fp == NULL)
    {
        printf("error while opening the file\n");
        exit(0);
    }
    int fs = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '#')
        {
            isPreprocessor = 1;
            printf("#");
            buffer[0] = '#';
        }
        else if (isPreprocessor == 1 && ch == '<')
        {
            printf("<");
            j = 0; // Reset the buffer index
            while ((ch = fgetc(fp)) != EOF && ch != '>')
            {
                buffer[j++] = ch;
                printf("%c", ch);
            }
            buffer[j++] = '>';
            printf("%c", ch);
            buffer[j] = '\0';
            printf(" is library\n");
            j = 0;
            isPreprocessor = 0; // Reset the preprocessor flag
        }
        else if (fs == 1 && (ch == 'd' || ch == 's' || ch == 'c'))
        {
            if (ch == 'd')
                printf("%%d is format specifier for signed integer\n");
            else if (ch == 's')
                printf("%%s is format specifier for strings\n");
            else if (ch == 'c')
                printf("%%c is format specifier for characters\n");
            fs = 0;
        }
        else
        {
            if (fs == 1)
            {
                printf("%% is modulus operator\n");
                fs = 0;
                goto here;
            }
            for (i = 0; i < 8; ++i)
            {
                if (ch == special[i])
                {
                    printf("%c is a special character\n", ch);
                }
            }
            for (i = 0; i < 6; ++i)
            {
                if (ch == operators[i])
                {
                    int thisflag = 0;
                    int k = 0;
                    while (buffer[k] != '\0')
                    {
                        if (!isdigit(buffer[k]))
                        {
                            thisflag = 1; // character contains alphabets too, so not constant.
                            break;
                        }
                        k++;
                    }
                    if (thisflag == 0)
                    {
                        printf("%s is constant\n", buffer);
                    }
                    else
                    {
                        printf("%s is identifier\n", buffer);
                    }
                    memset(buffer, '\0', 20);
                    j = 0;
                    if (ch == operators[0])
                        printf("%c is addition operator\n", ch);
                    else if (ch == operators[1])
                        printf("%c is subtraction operator\n", ch);
                    else if (ch == operators[2])
                        printf("%c is multiplication operator\n", ch);
                    else if (ch == operators[3])
                        printf("%c is division operator\n", ch);
                    else if (ch == operators[4])
                    {
                        fs = 1; // printf("%c is modulus operator\n",ch);
                    }
                    else if (ch == operators[5])
                        printf("%c is assignment operator\n", ch);
                }
            }
            if (ch == ',' || ch == '.' || ch == ':' || ch == ';')
            {
                int thisflag = 0;
                int k = 0;
                while (buffer[k] != '\0')
                {
                    if (!isdigit(buffer[k]))
                    {
                        thisflag = 1; // character contains alphabets too, so not constant.
                        break;
                    }
                    k++;
                }
                if (thisflag == 0)
                {
                    printf("%s is constant\n", buffer);
                }
                else
                {
                    printf("%s is identifier\n", buffer);
                }
                memset(buffer, '\0', 20);
                j = 0;
                if (j != 0)
                {
                    printf("%s is identifier\n", buffer);
                    memset(buffer, '\0', 20);
                    j = 0;
                }
                printf("%c is punctuator\n", ch);
            }
            if (isalnum(ch))
            {
                buffer[j++] = ch;
            }
            else if ((ch == ' ' || ch == '\n' || ch == '(') && (j != 0))
            {
                if (ch == '(')
                {
                    buffer[j++] = ch;
                    buffer[j] = '\0';
                    j = 0;
                    if (isLibFunction(buffer) == 1)
                    {
                        printf("%s) is library function\n", buffer);
                        memset(buffer, '\0', 20);
                    }
                    else if ((strcmp(buffer, "main(")) == 0)
                    {
                        printf("main() is identifier or primary function\n");
                        memset(buffer, '\0', 20);
                    }
                }
                else
                {
                    buffer[j] = '\0';
                    j = 0;
                    if (isKeyword(buffer) == 1)
                    {
                        printf("%s is keyword\n", buffer);
                        memset(buffer, '\0', 20);
                    }
                    else if (isLibFunction(buffer) == 1)
                    {
                        printf("%s) is library function\n", buffer);
                        memset(buffer, '\0', 20);
                    }
                    else if (isKeyword(buffer) != 1 && isPreprocessor == 1)
                    {
                        printf("%s is preprocessor directive\n", buffer);
                        memset(buffer, '\0', 20);
                    }
                    else
                    {
                        printf("%s is identifier\n", buffer);
                        memset(buffer, '\0', 20);
                    }
                }
            }
        }
    here:
        printf("");
    }
    fclose(fp);
    return 0;
}