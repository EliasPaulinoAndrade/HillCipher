/* 
* file: cipherHill.c
* Authors: Elias Paulino e Cibele Paulino
*
* Metodos/Funcoes usadas para implementar a Cifra de Hill
*
* Copyright (C) 2018 Elias Paulino <eliaspaulinoandrade@gmail.com>
* Copyright (C) 2018 Cibele Paulino <cibelepandrade@gmail.com>
* Data de atualização: 23 de setembro de 2018
*
* Para informacoes sobre escolha da matriz chave (encrypt_key) - restricoes e caracteristicas, como chegar na matriz inversa modular (decrypt_key) e funcionamento da * Cifra de Hill de maneira geral consulte o "README"
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
 * Retorno : dest_counter -> tamanho do vetor desti
 * Saída   : NENHUMA
 
 * Variáveis Locais: int dest_counter -> contador vetor destino, 
 *                   int text_counter -> contador do texto origem,
 *                   int except_counter -> contador do vetor de excessoes,
 *                   int has_exceptions -> guarda um TRUE ou FALSE (tem ou nao excessoes)
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
int remove_unwanted_words(char *dest, char *text, int text_size, char *exceptions) {
    
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

/*Função : Adiciona ao texto caractere(s) para que o numero de letras presente nesse texto seja multiplo da ordem da matriz (GAP)
 * 
 * Entrada : char *text -> vetor/ponteiro para vetor text, que guarda o texto origem, 
 *           int text_size -> tamanho da cadeia de caracteres do vetor text
 * Retorno : O novo tamanho que o texto possui (tamanho original + numero de caracteres adicionados)
 * Saída   : NENHUMA
 
 * Variáveis Locais: int space_to_fill -> guarda a quantidade de caracteres que devem ser acrescentados ao texto para que ele
 *                   tenha o numero de caracteres multiplo do GAP,
 *                   int i -> contador usado para adicionar os caracteres ao texto
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
int fill_missing_spaces(char *text, int text_size) {
    
    int i;
    int space_to_fill = text_size % GAP;   
    
    if(space_to_fill > 0){
        space_to_fill = (GAP - space_to_fill);
    }

    for (i = 0; i < space_to_fill; i++){

        text[text_size + i] = FILL_CHAR;

    }
    text[text_size + space_to_fill] = '\0';
    
    return text_size + space_to_fill;
}

/*Função : Formata o texto origem, chamando a funcao que deixa o texto lower case, a funcao que remove os caracteres indesejados, e a funcao que acrescenta os
 *         caracteres quando necessario
 * 
 * Entrada : char *dest -> Vetor/Ponteiro para vetor dest, que guardara o texto formatado,
 *           char *text -> vetor/ponteiro para vetor text, que guarda o texto origem, 
 *           int text_size -> tamanho da cadeia de caracteres do vetor text
 * Retorno : int text_size -> com o novo tamanho do texto
 * Saída   : NENHUMA
 
 * Variáveis Locais: NENHUMA
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
int format_text(char *dest, char *text, int text_size) {

    string_to_lower_case(text, text_size);
    text_size = remove_unwanted_words(dest, text, text_size, "");
    text_size = fill_missing_spaces(dest, text_size);

    return text_size;
}

/*Função : Codifica o texto fornecido, usando uma matriz chave
 * 
 * Entrada : char *dest -> guardara o texto codificado,
 *           char *text -> guarda o texto original,
 *           int text_size -> tamanho da cadeia de caracteres do vetor text,
 *           int key_matrix -> matriz usada como chave para codificar o texto
 * Retorno : retorna o text_size com o novo tamanho do texto
 * Saída   : NENHUMA
 
 * Variáveis Locais: char accord_text -> vetor de caracteres com o texto formatado
 *                   int gap_items -> matrix coluna que guardara cada bloco de caracteres
 *                   int mult_items -> matriz que guardara o matriz resultante da multiplicacao da matriz chave com gap_items
 *                   int pivo -> guarda o inicio de cada bloco de caracteres
 *                   int i -> contador é usado para percorrer o bloco de caracteres atual e, posteriormente a matriz resultante da multiplicacao
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
int encrypt(char *dest, char *text, int text_size, int key_matrix[][GAP]) {

    char accord_text[4000];

    text_size = format_text(accord_text, text, text_size);

    int gap_items[GAP][1];
    int mult_items [GAP][1];
    int pivo, i;
     
    //separa os caracteres em blocos, buscando o correspondente numerico de cada caracter
    for(pivo = 0; pivo < text_size; pivo += GAP) {
        for(i = pivo; i < pivo + GAP; i++) {

            gap_items[i - pivo][0] = char_to_number(accord_text[i]);
        }
        //multiplicando a matriz chave pela coluna
        matrix_multiply(1, GAP, GAP, mult_items, key_matrix, gap_items);
        
        //modulo do correspondente numerico na base do tamanho do alfabeto, e transforma num caracter correspondente (com base no teorema do pdf)
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
        }
    }
    dest[text_size] = '\0';
    return text_size;
}

/*Função : Escrever o texto no arquivo (...)
 * 
 * Entrada : char *text -> vetor/ponteiro para vetor texto, com o texto que sera escrito
 *           char *file_path -> vetor/ponteiro para vetor, com o nome do arquivo em que o texto sera escrito
 * Retorno : retorna 0 (OK) ou -1 (WRONG)
 * Saída   : texto no arquivo (...)
 
 * Variáveis Locais: File *file -> guarda a referencia para o arquivo aberto em que o texto sera escrito
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
int write_to_file(char *text, char *file_path) {
    FILE *file = fopen(file_path, "w");
    
    if(file == NULL) {
        return WRONG;
    }
    
    fprintf(file, "%s", text);
    fclose(file);
    
    return OK;
}

/*Função : Ler o texto de um arquivo (...)
 * 
 * Entrada : char *dest -> vetor/ponteiro para vetor em que sera guardada o texto lido
 *           int max_size -> tamanho maximo que o texto pode ter
 *           char *file_path -> vetor/ponteiro para vetor, com o nome do arquivo do qual o texto sera lido
 * Retorno : retorna 0 (OK) ou -1 (WRONG)
 * Saída   : NENHUMA
 
 * Variáveis Locais: File *file -> guarda a referencia para o arquivo aberto do qual o texto sera lido
 * Variáveis Globais Usadas : NENHUMA
 * Variáveis Globais Alteradas : NENHUMA
*/
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



