#include "csvlib.h"

void gerar_csv(unsigned int tam, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (!fp) {
        puts("Erro ao abrir o arquivo");
        exit(1);
    }

    //Gerar enumeração
    for (unsigned int i = 1; i <= ((tam*tam)+1); i++) {
        fprintf(fp, "%u, ", i);
    }
    fprintf(fp, "\n");

    fclose(fp);
}

void preencher_csv(unsigned char *m, unsigned int tam, char *filename, unsigned char rotulo)
{
    FILE *fp;
    fp = fopen(filename, "a");
    if (!fp) {
        puts("Erro ao abrir o arquivo");
        exit(1);
    }

    //Preencher com os valores
    for (unsigned int k = 0; k < (tam*tam); k++) {
        fprintf(fp, "%hhu, ", *(m + k));
    }
    fprintf(fp, "%s\n", rotulo ? "stroma" : "epithelium");

    fclose(fp);
}