#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAP 2
#define char_to_number(c) (c - 97)
#define number_to_char(i) (i + 97)

//CRIACAO DE STRING SEM /0


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
/*
Matrix *matrix_adjunt(Matrix *matrix) {
  
  
  return NULL;
}
*/

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

int remove_unwanted_words(char *dest, char *text, int text_size){
	/*remove os espaços do texto*/
	
	int i, j;	
	i = j = 0;
  	while(j < text_size){
    	if(text[j] != ' '){
      		dest[i] = text[j];
      		i++;
    	}
    	j++;
  	}

  	dest[i] = '\0';

  	return i;
}

int fill_missing_spaces(char *text, int text_size){
	/*preenche o texto para que ele tenha numero de letras multiplo do gap*/
	
	int space_to_fill = text_size % GAP;
  	if(space_to_fill != 0){
  	
  		int i;
  		for(i = 0; i < space_to_fill; i++){
  			text[text_size + i] = 'a';
		}
	    
	    text[text_size + space_to_fill] = '\0';
  	}
    
  	return text_size + space_to_fill;
}
 

int encrypt(char *dest, char *text, int text_size, int key_matrix[GAP][GAP]) {
  //encripta o texto usando uma matrix chave

  	char *switch_text;
  	text_size = remove_unwanted_words(dest, text, text_size);
  	switch_text = text;
  	text = dest;
  	dest = switch_text;
  
  	text_size = fill_missing_spaces(text, text_size);

  	int gap_items[GAP][1]; 
  	int mult_items[GAP][1];

  	int pivo, i;
  	for(pivo = 0; pivo < text_size; pivo += GAP) {
    	for(i = pivo; i < pivo + GAP; i++){ 
      		gap_items[i - pivo][0] = char_to_number(text[i]);
    	}
	
		matrix_multiply(1, GAP, GAP, mult_items, key_matrix, gap_items);	

    	for(i = 0; i < GAP; i++){
      		dest[pivo + i] = number_to_char(mult_items[i][0] % 26);
   		}
  	}
  
  	dest[text_size] = '\0';
  
  	return 1;  
}

int main(void) {
	int encrypt_key[GAP][GAP] = {
    	{2, 3},
    	{5, 7}
  	};
  	
  	int decrypt_key[GAP][GAP] = {
    	{19, 3},
    	{5, }
  	};


  	char dest[3067];
  	char text[3067] = "todas estas questoes devidamente ponderadas levantam duvidas sobre se a necessidade de renovacao processual ainda nao demonstrou convincentemente que vai participar na mudanca dos indices pretendidos o que temos que ter sempre em mente e que o julgamento imparcial das eventualidades estende o alcance e a importancia das diversas correntes de pensamento a nivel organizacional a execucao dos pontos do programa acarreta um processo de reformulacao e modernizacao das condicoes financeiras e administrativas exigidas acima de tudo e fundamental ressaltar que a valorizacao de fatores subjetivos desafia a capacidade de equalizacao dos paradigmas corporativos gostaria de enfatizar que o novo modelo estrutural aqui preconizado maximiza as possibilidades por conta das formas de acao todavia a continua expansao de nossa atividade causa impacto indireto na reavaliacao do processo de comunicacao como um todo e claro que a consulta aos diversos militantes pode nos levar a considerar a reestruturacao das condicoes inegavelmente apropriadas evidentemente a adocao de politicas descentralizadoras afeta positivamente a correta previsao dos metodos utilizados na avaliacao de resultados desta maneira a complexidade dos estudos efetuados representa uma abertura para a melhoria das direcoes preferenciais no sentido do progresso neste sentido o desafiador cenario globalizado oferece uma interessante oportunidade para verificacao das novas proposicoes no entanto nao podemos esquecer que o entendimento das metas propostas auxilia a preparacao e a composicao dos niveis de motivacao departamental nunca e demais lembrar o peso e o significado destes problemas uma vez que a revolucao dos costumes nao pode mais se dissociar do investimento em reciclagem tecnica a certificacao de metodologias que nos auxiliam a lidar com o aumento do dialogo entre os diferentes setores produtivos obstaculiza a apreciacao da importancia do levantamento das variaveis envolvidas percebemos cada vez mais que a constante divulgacao das informacoes deve passar por modificacoes independentemente das diretrizes de desenvolvimento para o futuro ainda assim existem duvidas a respeito de como o comprometimento entre as equipes apresenta tendencias no sentido de aprovar a manutencao de todos os recursos funcionais envolvidos por outro lado a hegemonia do ambiente politico nos obriga a analise do sistema de formacao de quadros que corresponde as necessidades no mundo atual a consolidacao das estruturas garante a contribuicao de um grupo importante na determinacao das posturas dos orgaos dirigentes com relacao as suas atribuicoes por conseguinte a mobilidade dos capitais internacionais e uma das consequencias dos conhecimentos estrategicos para atingir a excelencia o incentivo ao avanco tecnologico assim como o acompanhamento das preferencias de consumo assume importantes posicoes no estabelecimento do retorno esperado a longo prazo e importante questionar o quanto o consenso sobre a necessidade de qualificacao estimula a padronizacao do remanejamento dos quadros funcionais";
  
  	encrypt(dest, text, 3066, encrypt_key);
  	printf("%s", text);
  	
  	return 0;
}
