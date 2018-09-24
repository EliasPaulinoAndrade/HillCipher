/* 
* file: cipherHill.c
* Authors: Elias Paulino e Cibele Paulino
*
* Entrada: Sequencia de caracteres a ser codificada                                                                                         (ajeitar aqui)
* Saida: Sequencia de caracteres codificada e a sequencia decodificada
*
* Plataforma Alvo: Raspberry pi 3
* 
* O presente algoritmo foi implementado com referencia a Cifra de Hill desenvolvida em 1929 por Lester S. Hill, sendo um  
* trabalho concebido para a disciplina de Sistemas Embarcados do Curso de Engenharia de Computacao do IFCE - Campus Fortaleza. 
*
* As seguintes fontes foram usadas como referencia: Cifra de Hill <cts.luziania.ifg.edu.br/index.php/CTS1/article/download/100/pdf_30>, 
* Uma adaptação da Cifra de Hill para estudo de matrizes <http://www.repositorio.ufop.br/bitstream/123456789/9170/1/DISSERTA%C3%87%C3%83O_
* Adapta%C3%A7%C3%A3oCifraHill.pdf> e Criptografia e Algebra <http://www.mat.ufmg.br/~marques/CRIPTOGRAFIA.pdf>. 
*
* Copyright (C) 2018 Elias Paulino <eliaspaulinoandrade@gmail.com>
* Copyright (C) 2018 Cibele Paulino <cibelepandrade@gmail.com>
* Data de atualização: 23 de setembro de 2018
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config4x4_30.c"

#define TRUE 1
#define FALSE 0

#define OK 0
#define WRONG -1 


/*Função : Transformar um caractere em um correspondente numerico
 * 
 * Entrada : char c -> caractere inicial
 * Retorno : Correspondente numerico do caractere inicial ou -1 (WRONG)
 * Saída   : NENHUMA 
 
 * Variáveis Locais: int num -> guarda o correspondente numerico do caractere ou -1 caso nao tenha representacao no alfabeto utilizado
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
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

/*Função : Transformar um numero em um caractere correspondente
 * 
 * Entrada : int i -> numero inicial
 * Retorno : Caractere correspondente do numero inicial ou -1 (WRONG)
 * Saída   : NENHUMA 
 
 * Variáveis Locais: char charc -> guarda o caractere correspondente do numero ou -1 caso nao tenha representacao no alfabeto utilizado
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
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

/*Função : Mostrar o tamanho x profundidade de uma matriz, assim como uma matriz qualquer na saida
 * 
 * Entrada : int width -> width da matriz, 
 *           int height -> height da matriz,
 *           int matrix -> matriz
 * Retorno : NADA
 * Saída   : Tamanho da matriz no formato "width: x, height: y",
 *           matriz no formato n x n 
 
 * Variáveis Locais: int col -> guarda a coluna atual, 
 *                   int row -> guarda a linha atual.
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
void matrix_show(int width, int height, int matrix[][width]) {
    
    printf ("width: %d, height: %d\n", width, height);
    int col, row;

    for(row = 0; row < height; row++) {
        for(col = 0; col < width; col++) {

            printf("[%d]\t", matrix[row][col]);
        }

        printf("\n");
    }
}

/*Função : Multiplicar duas matrizes dadas (f_matrix e s_matrix) e guardar o resultado numa terceira matriz dada (result). Sendo que o numero 
 *         de colunas da primeira matriz (f_matrix) deve ser igual ao numero de linhas da segunda matriz (s_matrix)
 * 
 * Entrada : int s_width -> width da s_matriz
 *           int f_height -> height da f_matrix
 *           int f_width -> width da f_matrix
 *           int result -> matriz que guardara o resultado da multiplicacao
 *           int f_matrix -> primeira matriz
 *           int s_matrix -> segunda matriz
 * Retorno : 0 (OK)
 * Saída   : NENHUMA
 
 * Variáveis Locais: pivo -> representa f_col e o s_row, que incrementam de forma igual,
 *                   f_row -> guarda a linha atual da primeira matriz
 *                   s_col -> guarda a coluna atual da segunda matriz
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
int matrix_multiply(int s_width, int f_height, int f_width, int result[][s_width], int f_matrix[][f_width], int s_matrix[][s_width]) {

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

/*Função : NAO ESTA SENDO USADA ... REAVALIAR A NECESSIDADE DA PRESENCA NO CODIGO
 * 
 * Entrada : 
 * Retorno : 
 * Saída   : 
 
 * Variáveis Locais: 
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
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

/*Função : Transformar todos os caracteres de um vetor de caracteres (string) em lower case
 * 
 * Entrada : char *text -> vetor/Ponteiro para vetor text (cadeia de caracteres origem)
 *           int text_size -> tamanho da cadeia de caracteres do vetor text
 * Retorno : NADA
 * Saída   : NENHUMA
 
 * Variáveis Locais: int i -> contador do vetor text
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
void string_to_lower_case(char *text, int text_size) {

    int i;
    for(i = 0; i < text_size; i++) {
        text[i] = tolower(text[i]);
    }
}

/*Função : Cria um novo texto, que possui apenas os caracteres desejados do texto origem
 * 
 * Entrada : char *dest -> Vetor/Ponteiro para vetor dest, que guardara os caracteres presentes no vetor origem que sejam validos,
 *           char *text -> vetor/ponteiro para vetor text, que guarda o texto origem, 
 *           int text_size -> tamanho da cadeia de caracteres do vetor text, 
 *           char *exceptions -> vetor/ponteiro para vetor exceptions, que guarda os caracteres indesejados
 * Retorno : 
 * Saída   : NENHUMA
 
 * Variáveis Locais: int dest_counter -> contador vetor destino, 
 *                   int text_counter -> contador do texto origem,
 *                   int except_counter -> contador do vetor de excessoes,
 *                   int has_exceptions -> guarda um TRUE ou FALSE (tem ou nao excessoes)
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
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
    
    if(space_to_fill > 0){
        space_to_fill = (GAP - space_to_fill);
    }

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
        //matrix_show(1, 4, gap_items);
        

        for(i = 0; i < GAP; i++) {            
            if(mult_items[i][0] < 0) {
                if((-mult_items[i][0] % ALPHABET_SIZE) == 0) {
                    dest[pivo + i] = number_to_char(0);
                }
                else{
                    dest[pivo + i] = number_to_char(ALPHABET_SIZE - (-mult_items[i][0]) % ALPHABET_SIZE);
                }        
            }
            else{                
                dest[pivo + i] = number_to_char(mult_items[i][0] % ALPHABET_SIZE);        
            }
           // printf("%d - %c\n", mult_items[i][0], dest[pivo + i]);

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
    
    int c, i = 0;
    while ((c = getc(file)) != EOF && i < max_size - 1) {
        dest[i++] = c;
    }
    dest[i] = '\0';
    
    fclose(file);
    return OK;
}

int main (int argc, char *argv[]) {
    
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

