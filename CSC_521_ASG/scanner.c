#include <stdio.h>
#include <string.h>
#include "ctype.h"

typedef enum
{
    read,
    write,
    id,
    literal,
    becomes,
    add,
    sub,
    mul,
    div,
    lparen,
    rparen,
    eof
} token;

char token_image[100];
int line = 1;

token scan()
{
    static int c = ' ';
    /* next available char; extra (int) width accommodates EOF */
    int i = 0; /* index into token_image */

    /* skip white space */
    while (isspace(c)) {
        c = getchar();
    }

    /* Check for comments */
    while (c == '/')
    {
        if (c == '/')
        {
            c = getchar();
            /* Multiline */
            if (c == '*')
            {
                char prev = ' ';
                while (prev != '*' || c != '/')
                {
                    prev = c;
                    c = getchar();
                    if (c == '\n')
                    {
                        line++;
                    }
                    if (c == EOF)
                    {
                        fprintf(stderr, "lexical error on line no %d\n", line);
                        fprintf(stderr, "unclosed comment");
                        exit(1);
                    }
                }
                c = getchar();
            }
            /* Single line */
            else if (c == '/')
            {
                while (c != '\n' && c != EOF){
                    c = getchar();
                };
            }
            /* Put back the c */
            else
            {
                ungetc(c, stdin);
                c = '/';
                break;
            }
        }
        c = getchar();
    }
    

    if (c == EOF)
        return eof;
    if (isalpha(c))
    {
        // Reading a word
        do
        {
            token_image[i++] = c;
            c = getchar();
        } while (isalpha(c) || isdigit(c) || c == '_');
        token_image[i] = '\0';
        if (c == '\n')
            line++;
        // Checking the task name
        // If read
        if (!strcmp(token_image, "read"))
            return read;
        // Else if write
        else if (!strcmp(token_image, "write"))
            return write;
        // Else return assigned variable
        else
            return id;
    }
    else if (isdigit(c))
    {
        do
        {
            token_image[i++] = c;
            c = getchar();
        } while (isdigit(c));
        token_image[i] = '\0';
        if (c == '\n')
            line++;
        return literal;
    }
    else
        switch (c)
        {
        case ':':
            if (c = getchar() != '=')
            {
                fprintf(stderr, "lexical error on line no %d\nThe symbol '=' is missing check the code once again", line+1);
                exit(1);
            }
            else
            {
                c = getchar();
                return becomes;
            }
            break;
        case '+':
            c = getchar();
            return add;
        case '-':
            c = getchar();
            return sub;
        case '*':
            c = getchar();
            return mul;
        case '/':
            c = getchar();
            return div;
        case '(':
            c = getchar();
            return lparen;
        case ')':
            c = getchar();
            return rparen;
        case '\n':
            line++;
        default:
            printf("lexical error on line no %d\nAn unexpected character got in the program", line+1);
            exit(1);
        }
}