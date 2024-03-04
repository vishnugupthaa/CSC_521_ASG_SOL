#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Define token types */
#define KEYWORD 1
#define IDENTIFIER 2
#define NUMBER 3
#define OPERATOR 4
#define SEPARATOR 5

/* Define keyword codes */
#define READ 1
#define WRITE 2

/* Define operator codes */
#define ASSIGNMENT 1
#define ADDITION 2
#define SUBTRACTION 3
#define MULTIPLICATION 4
#define DIVISION 5

/* Define separator codes */
#define NEWLINE 1
#define SPACE 2

/* Define symbol table entry */
typedef struct symbol_table_entry {
    char name[20];
    int type;
    int value;
} symbol_table_entry;

/* Define the symbol table */
symbol_table_entry symbol_table[100];
int num_symbols = 0;


/* Look up a keyword and return its code */
int lookup_keyword(char *str) {
    if (strcmp(str, "read") == 0) {
        return READ;
    } else if (strcmp(str, "write") == 0) {
        return WRITE;
    } else {
        return 0;
    }
}

/* Look up an identifier and return its index in the symbol table */
int lookup_identifier(char *str) {
    int i;
    for (i = 0; i < num_symbols; i++) {
        if (strcmp(str, symbol_table[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

/* Look up an operator and return its code */
int lookup_operator(char *str) {
    if (strcmp(str, ":=") == 0) {
        return ASSIGNMENT;
    } else if (strcmp(str, "+") == 0) {
        return ADDITION;
    } else if (strcmp(str, "-") == 0) {
        return SUBTRACTION;
    } else if (strcmp(str, "*") == 0) {
        return MULTIPLICATION;
    } else if (strcmp(str, "/") == 0) {
        return DIVISION;
    } else {
        return 0;
    }
}

/* Look up a separator and return its code */
int lookup_separator(char *str) {
    if (strcmp(str, "\n") == 0) {
        return NEWLINE;
    } else if (strcmp(str, " ") == 0) {
        return SPACE;
    } else {
        return 0;
    }
}

/* Add a symbol to the symbol table and return its index */
int add_symbol(char *name, int type, int value) {
    strcpy(symbol_table[num_symbols].name, name);
    symbol_table[num_symbols].type = type;
    symbol_table[num_symbols].value = value;
    num_symbols++;
    return num_symbols - 1;
}

/* Find a symbol in the symbol table and return its index */
int find_symbol(char *name) {
    int i;
    for (i = 0; i < num_symbols; i++) {
        if (strcmp(name, symbol_table[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

/* Get the next token from the input stream */
int get_token(FILE *fp, char *buffer) {
    int i = 0, c;

    /* Skip whitespace */
    while (isspace(c = fgetc(fp)));

    /* Handle keywords */
    if (isalpha(c)) {
        buffer[i++] = c;
        while (isalnum(c = fgetc(fp))) {
            buffer[i++] = c;
        }
                buffer[i] = '\0';
        ungetc(c, fp);
        return lookup_keyword(buffer);
    }

    /* Handle identifiers */
    if (islower(c)) {
        buffer[i++] = c;
        while (isalnum(c = fgetc(fp))) {
            buffer[i++] = c;
        }
        buffer[i] = '\0';
        ungetc(c, fp);
        return IDENTIFIER;
    }

    /* Handle operators */
    if (c == ':' || c == '+' || c == '-' || c == '*' || c == '/') {
        buffer[i++] = c;
        if ((c == ':' && (c = fgetc(fp)) == '=') || c == '+' || c == '-' || c == '*' || c == '/') {
            buffer[i++] = c;
            buffer[i] = '\0';
            return OPERATOR;
        } else {
            printf("Error: unexpected character\n");
            return -1;
        }
    }

    /* Handle numbers */
    if (isdigit(c)) {
        buffer[i++] = c;
        while (isdigit(c = fgetc(fp))) {
            buffer[i++] = c;
        }
        buffer[i] = '\0';
        ungetc(c, fp);
        return NUMBER;
    }

    /* Handle separators */
    if (c == '\n' || c == ' ') {
        buffer[i++] = c;
        buffer[i] = '\0';
        return SEPARATOR;
    }

    printf("Error: unexpected character\n");
    return -1;
}

/* The main function */
int main(int argc, char **argv) {
    /* Open the file for parsing */
    FILE *fp;
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", argv[1]);
        return 1;
    }

    /* Parse the program */
    char buffer[100];
    int token_type, keyword_code, operator_code, separator_code, symbol_index;
    int value1, value2, result;
    while ((token_type = get_token(fp, buffer)) != EOF) {
        printf("Token");
        if (token_type == KEYWORD) {
            keyword_code = lookup_keyword(buffer);
            if (keyword_code == READ) {
                /* Read a value from input and add it to the symbol table */
                get_token(fp, buffer);
                symbol_index = add_symbol(buffer, NUMBER, 0);
                scanf("%d", &symbol_table[symbol_index].value);
            } else if (keyword_code == WRITE) {
                /* Get the value of the specified symbol and write it to output */
                get_token(fp, buffer);
                symbol_index = find_symbol(buffer);
                if (symbol_index >= 0) {
                    printf("%d\n", symbol_table[symbol_index].value);
                }
            }
        } else if (token_type == IDENTIFIER) {
            /* Store the identifier name for later use */
            strcpy(buffer, symbol_table[num_symbols-1].name);

            /* Expect an assignment operator */
            get_token(fp, buffer);
            operator_code = lookup_operator(buffer);
            if (operator_code != ASSIGNMENT) {
                printf("Error: expected assignment operator\n");
                return 1;
            }

            /* Evaluate the expression */
            get_token(fp, buffer);
            symbol_index = find_symbol(buffer);
            if (symbol_index < 0) {
                printf("Error: undefined symbol %s\n", buffer);
                return 1;
            }
            value1 = symbol_table[symbol_index].value;

            get_token(fp, buffer);
            operator_code = lookup_operator(buffer);
            if (operator_code == MULTIPLICATION) {
                get_token(fp, buffer);
                symbol_index = find_symbol(buffer);
                if (symbol_index < 0) {
                    printf("Error: undefined symbol %s\n", buffer);
                    return 1;
                value2 = symbol_table[symbol_index].value;
                result = value1 * value2;
            } else {
                printf("Error: expected multiplication operator\n");
                return 1;
            }

            /* Update the value of the symbol in the symbol table */
            symbol_table[num_symbols-1].value = result;
        } else if (token_type == SEPARATOR) {
            separator_code = lookup_separator(buffer);
            if (separator_code == NEWLINE) {
                /* End of a line of code; continue parsing the next line */
                continue;
            } else if (separator_code == SPACE) {
                /* Ignore spaces */
                continue;
            }
        } else {
            printf("Error: unexpected token\n");
            return 1;
        }
    }

    /* Close the file and exit */
    fclose(fp);
    return 0;
}
}