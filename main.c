/* 
* file: main.c
* Authors: Elias Paulino e Cibele Paulino
*
* Main/ Interface para uso do algoritmo Cifra de Hill
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
* 
* Modo de Uso: 
* Os comando possiveis sao: enc <texto> -> encripta um texto e mostra na saida
*                           dec <texto>-> decripta um texto e mostra na saida
*                           example -> encripta e decripta um texto predefinido, com mais de 3000 caracteres, e depois mostra o resultado de ambos
*                           example <texto> -> encripta e decripta o texto enviado pelo usuario e depois mostra o resultado de ambos
*                           enc <texto> toFile <url> -> encripta um texto e escreve na saida definida pelo usuario
*                           decFromFile <url> -> decripta um texto contido em um arquivo escolhido pelo usuario e mostra na saida 
* Maximo de caracteres: 3900
* Esse material possui configuracoes possiveis que envolvem matrizes chaves de tamanhos diferentes, texto exemplo para encriptacao e decriptacao e dois tamanhos possiveis 
* de alfabeto, sao eles: config2x2_26.c -> possui uma matriz chave 2x2 e sua inversa modular, alfabeto com 26 letras (A-Z)
*                        config2x2_30.c -> possui uma matriz chave 2x2 e sua inversa modular, alfabeto com 30 letras (A-Z; "."; " "; ","; "\n"), ou seja, alfabeto com alguns 
*                                          caracteres pre-definidos
*                        config4x4_26 -> possui uma matriz chave 4x4 e sua inversa modular, alfabeto com 26 letras (A-Z)
*                        config4x4_30 -> possui uma matriz chave 4x4 e sua inversa modular, alfabeto com 30 letras (A-Z; "."; " "; ","; "\n"), ou seja, alfabeto com alguns 
*                                        caracteres pre-definidos
*						 config7x7_30 -> possui uma matriz chave 7x7 e sua inversa modular, alfabeto com 30 letras (A-Z; "."; " "; ","; "\n"), ou seja, alfabeto com alguns 
*                                        caracteres pre-definidos
* Para usar essas configuracoes eh necessario da include dos arquivos (#include<configuracao desejavel>). Tambem eh possivel criar e usar configuracoes personalizadas seguindo
* o padrao das existentes.
*/

#include "config7x7_30.c"
#include "cipherHill.c"

/*Função : Cifrar ou decifrar um texto fornecido com base em uma matriz chave 
 * 
 * Entrada : int argc -> quantidade de argumentos de linha de comando
 *           char *argv -> array de string com os argumentos de linha de comando
 *           
 * Retorno : 0
 * Saída   : Texto cifrado ou decifrado em arquivo especifico ou arquivo padrao de saida
 *           Erro 
 * Variáveis Locais: char dest -> vetor/ponteiro para vetor que guarda o texto final, pode ser o texto cifrado, o decifrado ou os dois (tendo seu uso reaproveitado)
 *                   char text -> vetor/ponteiro para vetor que guarda o texto original
 *                   int size -> tamanho depois da encriptacao ou decriptacao
 * Variáveis Globais Usadas : 
 * Variáveis Globais Alteradas : NENHUMA
*/

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