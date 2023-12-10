#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_MAXIMO 256 

#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

//Recebe uma matriz de unsigned char, a quantidade de linhas e de colunas, o valor máximo e o valor mínimo
void preencher_matriz(unsigned char*, unsigned int, unsigned int, int, int);

//Recebe uma matriz de unsigned char, a quantidade de linhas e de colunas
//Imprime a matriz seguindo as linhas e as colunas
void imprimir_matriz(unsigned char*, unsigned int, unsigned int);

//Recebe uma matriz para retorno, uma matriz de unsigned char, o tamanho da janela, a quantidade de linhas e de colunas
//Filtra os valores da matriz utilizando a média aritmética dos valores na janela
//Organiza os valores obtidos numa matriz de retorno
unsigned char  *filtrar_media(unsigned char*, unsigned char*, unsigned int, unsigned int, unsigned int);

//Recebe uma matriz de unsigned char, a quantidade de linhas e de colunas
//Imprime uma matriz destacando os seus valores não nulos com cores diferentes
void destacar_valores_nao_nulos(unsigned char*, unsigned int, unsigned int);

//Recebe duas matrizes de unsigned char, a quantidade de linhas e de colunas, e o valor máximo das matrizes
//Retorna uma matriz de coocorrências de tamanho QTDxQTD
unsigned char *gerar_matriz_scm(unsigned char*, unsigned char*, unsigned int, unsigned int, unsigned char);

//Recebe uma matriz de unsigned char, a quantidade de linhas e de colunas, e o nível de quantização
//Retorna uma matriz quantizada
unsigned char *quantizar(unsigned char*, unsigned int, unsigned int, unsigned int);