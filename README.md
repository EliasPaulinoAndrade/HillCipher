 # Cifra de Hill
 Authors: Elias Paulino e Cibele Paulino

Informações gerais sobre a Cifra de Hill, a escolha da matriz e a transformação dessa matriz na sua inversa modular.

 Plataforma Alvo: Raspberry pi 3
 
O presente algoritmo foi implementado com referencia a Cifra de Hill desenvolvida em 1929 por Lester S. Hill, sendo um trabalho concebido para a disciplina de Sistemas Embarcados do Curso de Engenharia de Computacao do IFCE - Campus Fortaleza. 

 As seguintes fontes foram usadas como referencia: Cifra de Hill <cts.luziania.ifg.edu.br/index.php/CTS1/article/download/100/pdf_30>, 
 Uma adaptação da Cifra de Hill para estudo de matrizes <http://www.repositorio.ufop.br/bitstream/123456789/9170/1/DISSERTA%C3%87%C3%83O_Adapta%C3%A7%C3%A3oCifraHill.pdf> 
 e Criptografia e Algebra <http://www.mat.ufmg.br/~marques/CRIPTOGRAFIA.pdf>. 

 - Copyright (C) 2018 Elias Paulino <eliaspaulinoandrade@gmail.com>
 - Copyright (C) 2018 Cibele Paulino <cibelepandrade@gmail.com>
 Data de atualização: 23 de setembro de 2018
 
 ## Modo de Uso: 
 Maximo de caracteres suportados eh: 3900. Os comando possiveis sao: 
- enc <texto> -> encripta um texto e mostra na saida
- dec <texto>-> decripta um texto e mostra na saida
- example -> encripta e decripta um texto predefinido, com mais de 3000 caracteres, e depois mostra o resultado de ambos
- example <texto> -> encripta e decripta o texto enviado pelo usuario e depois mostra o resultado de ambos
- enc <texto> toFile <url> -> encripta um texto e escreve na saida definida pelo usuario
- decFromFile <url> -> decripta um texto contido em um arquivo escolhido pelo usuario e mostra na saida 

O arquivo cipherHill.c possui todos os metodos/funcoes usados para implementar a Cifra de Hill.

Esse material possui configuracoes possiveis que envolvem matrizes chaves de tamanhos diferentes, texto exemplo para encriptacao e decriptacao e dois tamanhos possiveis de alfabeto, sao eles: 
- config2x2_26.c -> possui uma matriz chave 2x2 e sua inversa modular, alfabeto com 26 letras (A-Z);
- config2x2_30.c -> possui uma matriz chave 2x2 e sua inversa modular, alfabeto com 30 letras (A-Z; "."; " "; ","; "\n"), ou seja, alfabeto com alguns caracteres pre-definidos;
- config4x4_26 -> possui uma matriz chave 4x4 e sua inversa modular, alfabeto com 26 letras (A-Z);
- config4x4_30 -> possui uma matriz chave 4x4 e sua inversa modular, alfabeto com 30 letras (A-Z; "."; " "; ","; "\n"), ou seja, alfabeto com alguns 
- caracteres pre-definidos.

Para usar essas configuracoes eh necessario da include dos arquivos (#include<configuracao desejavel>). Tambem eh possivel criar e usar configuracoes personalizadas seguindo
 o padrao das existentes.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Sobre a Cifra de Hill

Cifra de Hill (Criptografia em alfabeto algébrico) é um método criptográfico que foi inventado pelo matemático americano Lester S. Hill em 1929. Ele utiliza-se da álgebra linear para codificar e decodificar uma mensagem através da multiplicação de matrizes.

Abaixo, o estudo refere-se a cifragem utilizando uma matriz 2x2 e com o alfabeto padrão de 26 letras.

## Codificar
Primeiro converte-se as letras em números, logo após agrupa-se os números 2 a 2 e multiplicam-se cada grupo por uma matriz quadrada de ordem 2, que seja inversível (ou seja, com determinante ≠ 0). Os números resultantes são novamente passados para letras, e assim tem-se a mensagem codificada.
Caso algum resultado da multiplicação seja um número maior que o número de letras do alfabeto utilizado, assim utiliza-se o resto da divisão desse número pelo número de letras do alfabeto, que no nosso caso é 26, pois estamos considerando o alfabeto Inglês. Supõe-se que cada letra de texto comum (mensagem que ainda não foi codificada) e de texto cifrado, excetuando o Z, tem o valor numérico que especifica sua posição no alfabeto padrão.

A B C D E F G H I J  L  K  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 

Escolhe-se uma matriz 2×2 com entradas inteiras para efetuar a codificação,  M = [a1,1 a1,2 | a2,1 a2,2] que seja inversível, e que seu determinante seja coprimo com 26, isto é, não possua fatores primos em comum, esta condição é importante para podermos encontrar a inversa dessa matriz módulo 26.
Agrupam-se letras sucessivas do texto comum em pares (pois a matriz é 2x2), adicionando uma letra fictícia para completar a mensagem, caso o texto comum tenha um número ímpar de letras, e substituem-se cada letra de texto comum pelo seu valor numérico.
Converte-se cada par sucessivo de letras de texto comum em um vetor-coluna V = [p1 | pe] forma-se o produto A.p, que será o correspondente vetor cifrado. Converte-se cada vetor cifrado em seu equivalente alfabético.

OBS: Quando esse valor do vetor cifrado for maior que 26 usa-se o resíduo modular. 
ex: 56
56%26 = 4 
Dessa forma usa-se o 4 no lugar do 56

Teorema : Dados um inteiro a e um módulo m, quaisquer, se R = resto de |a|/m então o residuo r de módulo m é dado por: 
- r = R se a >= 0
- r = m-R se a < 0 e R != 0
- r = 0 se a < 0 e R != 0

## Decodificar
Primeiro transforma-se a matriz inicial na sua matriz inversa modular. Em Aritmética Modular, uma matriz quadrada é invertível se, e somente se, det A ≠ 0. A inversa de det A(mod 26) é dada por:
A(inverso) = (a 11 a 22 − a 12 a 21 ) (inverso) . [a1,1 -a1,2 | -a2,1 a2,2] mod(26)

Para facilitar, o inverso modular do determinante da matriz inicial na base 26 pode ser obtido com o auxilio da sequencia abaixo:
a           1  3  5  7  9  11  15  17  19  21  23  25
a(inverso)  1  9 21  15 3  19  7   23  11   5  17  25 

Dessa forma, se o determinante da matriz inicial for 3, o seu inverso modular será 9. Esse valor será então multiplicado com a matriz adjunta da matriz inicial. Por fim, faz-se o mod(26) da matriz resultante. Obtendo-se então a matriz chave para decriptar o texto.  
Se quisermos decifrar a mensagem codificada para mensagem comum, basta aplicar a matriz inversa em cada um dos vetores cifrados, isto é, multiplicamos a esquerda a matriz inversa de A por cada um dos vetores cifrados, e assim obtemos os equivalentes alfabéticos destes vetores que fornecem a mensagem já decifrada.

Para usar alfabetos alternativos, como com 30 caracteres/letras, basta basear a escolha da matriz com determinannte coprimo de 30 e fazer todas as operações utilizando o modulo de 30. 

