#include <stdio.h>
#include <stdlib.h>

//Recebe uma matriz de unsigned char, o tamanho da matriz, e o nome do arquivo
//Gera um arquivo CSV com o cabeçalho
void gerar_csv( unsigned int, char *);

//Recebe uma matriz de unsigned char, o tamanho da matriz, o nome do arquivo e o rótulo (0 ou 1)
//Preenche um arquivo CSV com os dados
void preencher_csv(unsigned char *, unsigned int, char *,unsigned int );
