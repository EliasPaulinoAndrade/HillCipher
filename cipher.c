#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//checar ponteiro vazio sempre que usar malloc
//usar menos mallocs

typedef struct {
  int *mat;
  int width;
  int height; 
} Matrix;

Matrix matrix_init(int height, int width, int *matt){
  /*aloca matriz e retorna*/

  Matrix mat;
  mat.width = width;
  mat.height = height;
  
  mat.mat = matt;
  
  return mat;
}

int matrix_index(int row, int col, int width){
  return row * width + col; 
}

void matrix_show(Matrix *matrix){
  /*printa matrix*/

  printf("width: %d, height: %d\n", matrix->width, matrix->height);
  
  int col, row;
  
  for(row = 0; row < matrix->height; row++) {
    for(col = 0; col < matrix->width; col++) {
      printf("[%d]\t", matrix->mat[ matrix_index(row, col, matrix->width) ]);
    }
    printf("\n");
  }
}

Matrix *matrix_adjunt(Matrix *matrix) {
  /*calcula matrix adjunta*/
  
  return NULL;
}

int matrix_multiply(Matrix *mat, Matrix *f_matrix, Matrix *s_matrix) {
  /*faz a multiplicacao de duas matrizes*/

  //pra multiplicar, a primeira matriz deve ter largura igual a altura a da segunda
  if (f_matrix->width != s_matrix->height) {
    return -1;
  }

  //a matriz resultado tem a altura da primeira matriz e a largura da segunda
  if (mat->height != f_matrix->height || mat->width != s_matrix->width) {
    return -1;
  }

  //o pivo é eh o f_col e o s_row, que sao os mesmos
  int pivo, f_row, s_col;
  for(f_row = 0; f_row < f_matrix->height; f_row++) {
    for(s_col = 0; s_col < s_matrix->width; s_col++) {

      mat->mat[ matrix_index(f_row, s_col, mat->width) ] = 0;
      for(pivo = 0; pivo < f_matrix->width; pivo++) {

        mat->mat[matrix_index(f_row, s_col, mat->width)] += f_matrix->mat[ matrix_index(f_row, pivo, f_matrix->width) ] * s_matrix->mat[ matrix_index(pivo, s_col, s_matrix->width) ];
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

int remove_spaces(char *text, char *dest, int text_size){

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

  return i - 1;
}

int encrypt(char *dest, char *text, int text_size, Matrix *key_matrix) {
  //encripta o texto usando uma matrix chave

  //matrix chave tem que ser quadrada
  if(key_matrix->width != key_matrix->height) {
    return -1;
  }

  //must be par CHANGE IT
  if(text_size%2 != 0){
    text[text_size] = 'a';
    text_size++;

    
    printf("%s - %d - \n", text, text_size);
  }


  int gap = key_matrix->width;
  int gap_items[gap][1]; 
  int mult_items[gap][1];

  int pivo, i;
  for(pivo = 0; pivo < text_size; pivo += gap) {
    for(i = pivo; i < pivo + gap; i++){ 
      gap_items[i - pivo][0] = text[i] - 97; 
    }

    Matrix gap_matrix = matrix_init(gap, 1, &gap_items[0][0]);
    Matrix mult_matrix = matrix_init(gap, 1, &mult_items[0][0]);
    matrix_multiply(&mult_matrix, key_matrix, &gap_matrix);

    for(i = 0; i < gap; i++){
      dest[pivo + i] = mult_matrix.mat[ matrix_index(i, 0, mult_matrix.width) ] % 26 + 97;
    }
  }
  return 1;  
}

int main(void) {

  int matt[2][2] = {
    {25, 22},
    {1, 23}
  };
  Matrix mat = matrix_init(2, 2, &matt[0][0]);

  char dest[50];
  char *text = "elias paulino";
  
  int size = remove_spaces(text, dest, 12);
  text = dest;


  //encrypt(dest, text, size, &mat);

  printf("%s - %d - \n", text, size);
  return 0;
}
