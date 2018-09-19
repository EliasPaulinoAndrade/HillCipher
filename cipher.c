#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define GAP 2
#define FILL_CHAR ' '
#define ALPHABET_SIZE 30

#define TEXT_EXAMPLE "Todas estas questoes, devidamente ponderadas, levantam duvidas sobre se a mobilidade dos capitais internacionais possibilita uma melhor visao global dos paradigmas corporativos. Acima de tudo, e fundamental ressaltar que a estrutura atual da organizacao pode nos levar a considerar a reestruturacao do retorno esperado a longo prazo. O incentivo ao avanco tecnologico, assim como a continua expansao de nossa atividade agrega valor ao estabelecimento do sistema de formacao de quadros que corresponde as necessidades. Caros amigos, o surgimento do comercio virtual oferece uma interessante oportunidade para verificacao do sistema de participacao geral. A nivel organizacional, o desenvolvimento continuo de distintas formas de atuacao afeta positivamente a correta previsao dos procedimentos normalmente adotados. \n\
          		No entanto, nao podemos esquecer que o consenso sobre a necessidade de qualificacao exige a precisao e a definicao da gestao inovadora da qual fazemos parte. Podemos ja vislumbrar o modo pelo qual o comprometimento entre as equipes maximiza as possibilidades por conta do orcamento setorial. A certificacao de metodologias que nos auxiliam a lidar com o aumento do dialogo entre os diferentes setores produtivos nos obriga a analise de alternativas as solucoes ortodoxas. \n\
				Desta maneira, a valorizacao de fatores subjetivos e uma das consequencias dos metodos utilizados na avaliacao de resultados. Todavia, o julgamento imparcial das eventualidades estimula a padronizacao dos conhecimentos estrategicos para atingir a excelencia. Ainda assim, existem duvidas a respeito de como a complexidade dos estudos efetuados deve passar por modificacoes independentemente das direcoes preferenciais no sentido do progresso. \n\
				Neste sentido, o inicio da atividade geral de formacao de atitudes prepara-nos para enfrentar situacoes atipicas decorrentes das posturas dos orgaos dirigentes com relacao as suas atribuicoes. O que temos que ter sempre em mente e que o acompanhamento das preferencias de consumo representa uma abertura para a melhoria dos modos de operacao convencionais. Pensando mais a longo prazo, a consolidacao das estruturas causa impacto indireto na reavaliacao do levantamento das variaveis envolvidas. \n\
				E claro que a crescente influencia da midia talvez venha a ressaltar a relatividade dos relacionamentos verticais entre as hierarquias. As experiencias acumuladas demonstram que a expansao dos mercados mundiais acarreta um processo de reformulacao e modernizacao das diversas correntes de pensamento. Por outro lado, a hegemonia do ambiente politico auxilia a preparacao e a composicao das regras de conduta normativas. Nunca e demais lembrar o peso e o significado destes problemas, uma vez que o fenomeno da Internet nao pode mais se dissociar dos indices pretendidos. \n\
  		        Por conseguinte, a consulta aos diversos militantes desafia a capacidade de equalizacao do investimento em reciclagem tecnica. Do mesmo modo, o entendimento das metas propostas promove a alavancagem das formas de acao. No mundo atual, a determinacao clara de objetivos apresenta tendencias no sentido de aprovar a manutencao dos niveis de motivacao departamental."

int char_to_number(char c){
	
	switch(c){
		case ' ':
			return 26;
		case '.':
			return 27;
		case ',':
			return 28;
		case '\n':
			return 29;
		default:
			if(c >= 'a' && c <= 'z') {
				return c - 97;
			}
			return -1;
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
		case 29:
			return '\n';
		default:
			if(i >= 0 && i <= 25) {
				return i + 97;
			}
			return -1;
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

void string_to_lower_case(char *text){
	
	int i;
	for(i = 0; i < strlen(text); i++){
		text[i] = tolower(text[i]);	
	}
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
		  
    	if(has_exceptions == FALSE && char_to_number(text[text_counter]) != -1){
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
 
int format_text(char *dest, char *text, int text_size){
	
	string_to_lower_case(text);
	text_size = remove_unwanted_words(dest, text, text_size, "");
	text_size = fill_missing_spaces(dest, text_size);
	
	return text_size;
}

int encrypt(char *dest, char *text, int text_size, int key_matrix[GAP][GAP]) {
  //encripta o texto usando uma matrix chave

  	char accord_text[text_size];
  
  	text_size = format_text(accord_text, text, text_size);

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
    	{23, 3},
    	{5, 28}
  	};
  	
	char dest[4000];
  	char text[4000] = TEXT_EXAMPLE;
  	
  	int size;
  
  	size = encrypt(dest, text, strlen(text), encrypt_key);
  	printf("%s [SIZE: %d]\n\n", dest, size);
  	
  	encrypt(text, dest, size, decrypt_key);
  	printf("%s\n\n", text);	

  	return 0;
}
