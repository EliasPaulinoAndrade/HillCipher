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

int remove_spaces(char *dest, char *text, int text_size){

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
	
	int space_to_fill = text_size % GAP;
  	if(space_to_fill != 0){
  	
  		int i;
  		for(i = 0; i < space_to_fill; i++){
  			text[text_size + i] = 'a';
		}
	
  	}
  
  	return text_size + space_to_fill;
}
 

int encrypt(char *dest, char *text, int text_size, int key_matrix[GAP][GAP]) {
  //encripta o texto usando uma matrix chave

  text_size = remove_blank_spaces(dest, text, text_size);
  text = dest;
  
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

  int mat[GAP][GAP] = {
    {25, 22},
    {1, 23}
  };

  char dest[449];
  char text[449] = "o cuidado em identificar pontos criticos na valorizacao de fatores subjetivos causa impacto indireto na reavaliacao dos conhecimentos estrategicos para atingir a excelencia no mundo atual a hegemonia do ambiente politico agrega valor ao estabelecimento do processo de comunicacao como um todo por conseguinte a estrutura atual da organizacao acarreta um processo de reformulacao e modernizacao das condicoes financeiras e administrativas exigidas";
  
  encrypt(dest, text, 446, mat);

  printf("%s", text);
  return 0;
}
