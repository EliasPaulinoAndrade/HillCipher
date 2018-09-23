#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.c"

#define TRUE 1
#define FALSE 0

#define OK 0
#define WRONG -1 

int char_to_number(char c) {
    
    int num = WRONG;
    switch(c) {

	case ' ':
            num = 26;
            break;
	case '.':
            num = 27;
            break;
	case ',':
            num = 28;
            break;
	case '\n':
            num = 29;
            break;
	default:
            if(c >= 'a' && c <= 'z') {
                num = c - 97;
            }
    }

    if(num >= ALPHABET_SIZE) {
        return WRONG;
    }
    
    return num;
}

char number_to_char(int i) {

    char charc = WRONG;
    
    if(i >= ALPHABET_SIZE) {
        return charc;
    }
    
    switch(i) {

	case 26:
            charc = ' ';
            break;
	case 27:
            charc = '.';
            break;
	case 28:
            charc = ',';
            break;
	case 29:
            charc = '\n';
            break;
	default:
            if(i >= 0 && i <= 25) {
                charc = i + 97;
            }
    }
    
    return charc;
}

void matrix_show(int width, int height, int matrix[][width]) {

    /*imprime a matriz*/
    
    printf ("width: %d, height: %d\n", width, height);
    int col, row;

    for(row = 0; row < height; row++) {
        for(col = 0; col < width; col++) {

            printf("[%d]\t", matrix[row][col]);
        }

        printf("\n");
    }
}

int matrix_multiply(int s_width, int f_height, int f_width, int result[][s_width], int f_matrix[][f_width], int s_matrix[][s_width]) {

    /*multiplica duas matrizes*/

    /*o pivo eh o f_col e o s_row, que sao os mesmos*/
    int pivo, f_row, s_col;
    for(f_row = 0; f_row < f_height; f_row++) {
        for(s_col = 0; s_col < s_width; s_col++) {
            result[f_row][s_col] = 0;
            for(pivo = 0; pivo < f_width; pivo++) {
                
                result[f_row][s_col] += f_matrix[f_row][pivo] * s_matrix[pivo][s_col];
            }
        }
    }
    return OK;
}

int modular_inverse(int num, int base){

    /*encontra o inverso modular de um numero em uma certa base*/
    int inverse;
    for(inverse = 1; inverse < base; inverse++) {
        
        /*o inverso em um numero em uma base um numero cuja multiplicacao por ele da resto 1 na tal base*/
        if((inverse * num) % base == 1) {
            return inverse;
        }
    }
    return WRONG;
}

void string_to_lower_case(char *text, int text_size) {

    int i;
    for(i = 0; i < text_size; i++) {
        text[i] = tolower(text[i]);
    }
}


int remove_unwanted_words(char *dest, char *text, int text_size, char *exceptions) {

    /*remove os espacos do texto*/
    
    int dest_counter, text_counter, except_counter, has_exceptions;
    dest_counter = text_counter = except_counter = has_exceptions = 0;
    while (text_counter < text_size) {

        has_exceptions = FALSE;
        for(except_counter = 0; except_counter < strlen(exceptions); except_counter++) {

            if(exceptions[except_counter] == text[text_counter]) {

                has_exceptions = TRUE;
            }
        }
        
        if(has_exceptions == FALSE && char_to_number(text[text_counter]) != WRONG) {
            dest[dest_counter] = text[text_counter];
            dest_counter++;
        }
        text_counter++;
    }

    dest[dest_counter] = '\0';
    
    return dest_counter;
}

int fill_missing_spaces(char *text, int text_size) {

    /*preenche o texto para que ele tenha numero de letras multiplo do gap*/

    int space_to_fill = text_size % GAP;

    int i;
    for (i = 0; i < space_to_fill; i++){

        text[text_size + i] = FILL_CHAR;

    }
    text[text_size + space_to_fill] = '\0';
    
    return text_size + space_to_fill;
}

int format_text(char *dest, char *text, int text_size) {

    string_to_lower_case(text, text_size);
    text_size = remove_unwanted_words(dest, text, text_size, "");
    text_size = fill_missing_spaces(dest, text_size);

    return text_size;
}

int encrypt(char *dest, char *text, int text_size, int key_matrix[][GAP]) {

    /*encripta o texto usando uma matrix chave*/
    char accord_text[4000];

    text_size = format_text(accord_text, text, text_size);

    int gap_items[GAP][1];
    int mult_items [GAP][1];
    int pivo, i;

    for(pivo = 0; pivo < text_size; pivo += GAP) {
        for(i = pivo; i < pivo + GAP; i++) {

            gap_items[i - pivo][0] = char_to_number(accord_text[i]);
        }

        matrix_multiply(1, GAP, GAP, mult_items, key_matrix, gap_items);

        for(i = 0; i < GAP; i++) {
            if(mult_items[i][0] < 0) {
                dest[pivo + i] = number_to_char(ALPHABET_SIZE - (-mult_items[i][0]) % ALPHABET_SIZE);
            }
            else{                
                dest[pivo + i] = number_to_char(mult_items[i][0] % ALPHABET_SIZE);        
            }
        }
    }
    dest[text_size] = '\0';
    return text_size;
}

int write_to_file(char *text, char *file_path) {
    FILE *file = fopen(file_path, "w");
    
    if(file == NULL) {
        return WRONG;
    }
    
    fprintf(file, "%s", text);
    fclose(file);
    
    return OK;
}

int read_from_file(char *dest, int max_size, char *file_path) {
    FILE *file = fopen(file_path, "r");
    
    if(file == NULL) {
        return WRONG;
    }
    
    char c, i = 0;
    while ((c = getc(file)) != EOF && i < max_size - 1) {
        dest[i++] = c;
    }
    dest[i] = '\0';
    
    fclose(file);
    return OK;
}

int main (int argc, char *argv[]) {

    int encrypt_key[GAP][GAP] = {
        {2,3},
        {5,7}
    };

    int decrypt_key[GAP][GAP] = {
        {23,3},
        {5,28}
    };
    
    char dest[4000];
    char text[4000] = "";
    int size;
    
    if(argc == 3 && strcmp(argv[1], "enc") == 0) {
        strcat(text, argv[2]);
        
        size = encrypt(dest, text, strlen(text), encrypt_key);
        printf("%s", dest);
        
    }
    else if(argc == 3 && strcmp(argv[1], "dec") == 0) {
        strcat(text, argv[2]);
        
        size = encrypt(dest, text, strlen(text), decrypt_key);
        printf("%s", dest);
        
    }else if(argc == 2 && strcmp(argv[1], "example") == 0) {
        strcat(text, TEXT_EXAMPLE);

        size = encrypt(dest, text, strlen(text), encrypt_key);
        printf("Cifrado: {%s}\n\n", dest);

		size = encrypt(text, dest, size, decrypt_key);
        printf("Decrifrado: {%s}\n", text);
	
    }else if(argc == 3 && strcmp(argv[1], "example") == 0) {
        strcat(text, argv[2]);

        size = encrypt(dest, text, strlen(text), encrypt_key);
        printf("Cifrado: {%s}\n\n", dest);

		size = encrypt(text, dest, size, decrypt_key);
        printf("Decrifrado: {%s}\n", text);
	
    }
    else if(argc == 5 && strcmp(argv[1], "enc") == 0 && strcmp(argv[3], "toFile") == 0) {
        strcat(text, argv[2]);
        
        size = encrypt(dest, text, strlen(text), encrypt_key);
        if(write_to_file(dest, argv[4]) == OK) {
            printf("Done.\n");
        }else {
            printf("Error While Writing in File.\n");
        }
    }else if(argc == 3 && strcmp(argv[1], "decFromFile") == 0) {
        char file_text[4000];
        
        if(read_from_file(file_text, 4000, argv[2]) == OK) {
	     strcat(text, file_text);
             size = encrypt(dest, text, strlen(text), decrypt_key);
        
             printf("%s", dest); 
        }else {
            printf("Error While Reading from File.\n");
        }
    }
    else {
        printf("Invalid Command.\n");
    }
    return 0;
}

