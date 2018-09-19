#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define GAP 2
#define FILL_CHAR ' '
#define ALPHABET_SIZE 29

int char_to_number(char c){
	switch(c){
		case ' ':
			return 26;
		case '.':
			return 27;
		case ',':
			return 28;
		default:
			return c - 97;
	}
}

char number_to_char(int i){
	switch(i){
		case 26:
			return ' ';
		case 27:
			return '.';
		case 28:
			return ',';
		default:
			return i + 97;
	}
}

void matrix_show(int width, int height, int matrix[height][width]){
  /*printa matrix*/

  	printf("width: %d, height: %d\n", width, height);
  
  	int col, row;
  
  	for(row = 0; row < height; row++) {
    	for(col = 0; col < width; col++) {
      		printf("[%d]\t", matrix[row][col]);
    	}
    	printf("\n");
  	}
}

int matrix_multiply(int s_width, int f_height, int f_width, int result[f_height][s_width], int f_matrix[f_height][f_width], int s_matrix[f_width][s_width]) {
  	/*faz a multiplicacao de duas matrizes*/
  
  	//o pivo é eh o f_col e o s_row, que sao os mesmos
  	int pivo, f_row, s_col;
  	for(f_row = 0; f_row < f_height; f_row++) {
    	for(s_col = 0; s_col < s_width; s_col++) {

      		result[f_row][s_col] = 0;
      		for(pivo = 0; pivo < f_width; pivo++) {
        		result[f_row][s_col] += f_matrix[f_row][pivo] * s_matrix[pivo][s_col];
      		}  
    	}
  	} 

  return 1;
}

int modular_inverse(int num, int base) {
  	/*encontra o inverso modular de um num em uma certa base*/

  	int inverse;
  	for(inverse = 1; inverse < base; inverse++) {

    	//o inverso de um numero em uma base é um numero cuja multiplicacao por ele da resto 1 na tal base
    	if((inverse * num) % base == 1) {
      		return inverse;
    	}
  	} 
  	return -1;
}

int remove_unwanted_words(char *dest, char *text, int text_size, char *exceptions){
	/*remove os espaços do texto*/
	
	int dest_counter, text_counter, except_counter, has_exceptions;	
	dest_counter = text_counter = except_counter = has_exceptions = 0;
  	while(text_counter < text_size){
  		has_exceptions = FALSE;
  		for(except_counter = 0; except_counter< strlen(exceptions); except_counter++){
  			if(exceptions[except_counter] == text[text_counter]){
				has_exceptions = TRUE;	
			}
		}
		  
    	if(has_exceptions == FALSE){
      		dest[dest_counter] = text[text_counter];
      		dest_counter++;
    	}
    	text_counter++;
  	}

  	dest[dest_counter] = '\0';

  	return dest_counter;
}

int fill_missing_spaces(char *text, int text_size){
	/*preenche o texto para que ele tenha numero de letras multiplo do gap*/
	
	int space_to_fill = text_size % GAP;
  	if(space_to_fill != 0){
  	
  		int i;
  		for(i = 0; i < space_to_fill; i++){
  			text[text_size + i] = FILL_CHAR;
		}
	    
	    text[text_size + space_to_fill] = '\0';
  	}
    
  	return text_size + space_to_fill;
}
 

int encrypt(char *dest, char *text, int text_size, int key_matrix[GAP][GAP]) {
  //encripta o texto usando uma matrix chave

  	char *accord_text = text;
  
  	text_size = fill_missing_spaces(accord_text, text_size);

  	int gap_items[GAP][1]; 
  	int mult_items[GAP][1];

  	int pivo, i;
  	for(pivo = 0; pivo < text_size; pivo += GAP) {
    	for(i = pivo; i < pivo + GAP; i++){ 
      		gap_items[i - pivo][0] = char_to_number(accord_text[i]);
    	}
	
		matrix_multiply(1, GAP, GAP, mult_items, key_matrix, gap_items);	

    	for(i = 0; i < GAP; i++){
      		dest[pivo + i] = number_to_char(mult_items[i][0] % ALPHABET_SIZE);
   		}
  	}
  
  	dest[text_size] = '\0';
  
  	return text_size;  
}

int main(int argc, char *argv[]) {
	
	int encrypt_key[GAP][GAP] = {
    	{2, 3},
    	{5, 7}
  	};
  	
  	int decrypt_key[GAP][GAP] = {
    	{22, 3},
    	{5, 27}
  	};
  	
	char dest[3067];
  	char text[3067] = "gostaria de enfatizar que o inicio da atividade geral de formacao de atitudes afeta positivamente a correta previsao do remanejamento dos quadros funcionais. e claro que a estrutura atual da organizacao estende o alcance e a importancia dos niveis de motivacao departamental. desta maneira, o surgimento do comercio virtual nos obriga a analise do fluxo de informacoes. no entanto, nao podemos esquecer que a competitividade nas transacoes comerciais prepara-nos para enfrentar situacoes atipicas decorrentes dos indices pretendidos. no mundo atual, o aumento do dialogo entre os diferentes setores produtivos cumpre um papel essencial na formulacao das regras de conduta normativas. nao obstante, a constante divulgacao das informacoes aponta para a melhoria das direcoes preferenciais no sentido do progresso. por outro lado, a adocao de politicas descentralizadoras acarreta um processo de reformulacao e modernizacao dos relacionamentos verticais entre as hierarquias. caros amigos, o julgamento imparcial das eventualidades maximiza as possibilidades por conta do sistema de participacao geral. do mesmo modo, a crescente influencia da midia garante a contribuicao de um grupo importante na determinacao do orcamento setorial. o que temos que ter sempre em mente e que o comprometimento entre as equipes exige a precisao e a definicao das condicoes financeiras e administrativas exigidas. percebemos, cada vez mais, que a hegemonia do ambiente politico e uma das consequencias dos metodos utilizados na avaliacao de resultados. acima de tudo, e fundamental ressaltar que o consenso sobre a necessidade de qualificacao estimula a padronizacao do retorno esperado a longo prazo. o incentivo ao avanco tecnologico, assim como a valorizacao de fatores subjetivos auxilia a preparacao e a composicao de alternativas as solucoes ortodoxas. todas estas questoes, devidamente ponderadas, levantam duvidas sobre se a consolidacao das estruturas causa impacto indireto na reavaliacao das novas proposicoes. neste sentido, a complexidade dos estudos efetuados obstaculiza a apreciacao da importancia do impacto na agilidade decisoria. as experiencias acumuladas demonstram que a continua expansao de nossa atividade ainda nao demonstrou convincentemente que vai participar na mudanca do levantamento das variaveis envolvidas. o incentivo ao avanco tecnologico, assim como a valorizacao de fatores subjetivos auxilia a preparacao e a composicao de alternativas as solucoes ortodoxas. todas estas questoes, devidamente ponderadas, levantam duvidas sobre se a consolidacao das estruturas causa impacto indireto na reavaliacao das novas proposicoes. neste sentido, a complexidade dos estudos efetuados obstaculiza a apreciacao da importancia do impacto na agilidade decisoria. as experiencias acumuladas demonstram que a continua expansao de nossa atividade ainda nao demonstrou convincentemente que vai participar na mudanca do levantamento das variaveis envolvidas. convincentemente que vai participar na mudanca do levantamento das variaveis envolvidas.";
  
  	int size;
  
  	size = encrypt(dest, text, strlen(text), encrypt_key);
  	printf("%s [SIZE: %d]\n\n", dest, size);
  	
  	encrypt(text, dest, size, decrypt_key);
  	printf("%s\n\n", text);

  	return 0;
}
