#include "op_matrizes.h"
#include "pgmlib.h"
#include <stdio.h>
#include <stdlib.h>

#define FOLDER "./oncotex_pgm"
#define LIN 16
#define COL 16
#define val_max 255
#define val_min 0
#define JANELA 9
#define maior_valor 255
#define QTDIMG 2


int main() {
    struct pgm imagem;
    char *nomeArquivo = NULL;

    nomeArquivo = malloc(100);

    if (nomeArquivo == NULL) {
        perror("Erro ao alocar memória para nomeArquivo");
        exit(EXIT_FAILURE);
    }

    snprintf(nomeArquivo, 100, "%s/nome_do_arquivo.pgm", FOLDER);

    readPGMImage(&imagem, nomeArquivo);
    
    printf("Imagem PGM Original:\n");
    viewPGMImage(&imagem);

    unsigned int linhas = 5;
    unsigned int colunas = 5;
    unsigned char *matriz1 = (unsigned char *)malloc(linhas * colunas * sizeof(unsigned char));
    unsigned char *matriz2 = (unsigned char *)malloc(linhas * colunas * sizeof(unsigned char));

    preencher_matriz(matriz1, linhas, colunas, 255, 0);
    preencher_matriz(matriz2, linhas, colunas, 255, 0);

    printf("\nMatriz Original 1:\n");
    imprimir_matriz(matriz1, linhas, colunas);

    printf("\nMatriz Original 2:\n");
    imprimir_matriz(matriz2, linhas, colunas);

    unsigned char *scm = gerar_matriz_scm(matriz1, matriz2, linhas, colunas, 255);

    unsigned char *matrizQuantizada = quantizar(matriz1, linhas, colunas, 5);

    printf("\nMatriz Quantizada:\n");
    imprimir_matriz(matrizQuantizada, linhas, colunas);

    unsigned char *matrizFiltrada = (unsigned char *)malloc(linhas * colunas * sizeof(unsigned char));
    filtrar_media(matrizFiltrada, matriz1, 3, linhas, colunas);

    printf("\nMatriz Filtrada:\n");
    imprimir_matriz(matrizFiltrada, linhas, colunas);

    free(matriz1);
    free(matriz2);
    free(scm);
    free(matrizQuantizada);
    free(matrizFiltrada);

    return 0;
}


