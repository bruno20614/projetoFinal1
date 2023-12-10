#include "op_matrizes.h"

void preencher_matriz(unsigned char *m, unsigned int lin, unsigned int col, int max, int min)
{
    for (unsigned int i = 0; i < lin*col; i++) {
        *(m + i) = (unsigned char)(rand()%max) + min;
    }
}

void imprimir_matriz(unsigned char *m, unsigned int lin, unsigned int col)
{
    for (unsigned int i = 0; i < lin; i++) {
        for (unsigned int j = 0; j < col; j++) {
            printf("[%03hhu] ", *((m + j) + (i*col)));
        }
        printf("\n");
    }
}

void destacar_valores_nao_nulos(unsigned char *m, unsigned int lin, unsigned int col)
{
    for (unsigned int i = 0; i < lin; i++) {
        for (unsigned int j = 0; j < col; j++) {
            if (*((m + j) + (i*col))) {
                printf("%s%03hhu%s ", GREEN, *((m + j) + (i*col)), RESET);
            } else {
                printf("%03hhu ", *((m + j) + (i*col)));
            }
        }
        printf("\n");
    }
}

unsigned char *gerar_matriz_scm(unsigned char *m, unsigned char *n, unsigned int lin, unsigned int col, unsigned char qtd)
{
    //Essas variáveis só existem para deixar o código mais didático e organizado
    //unsigned char i;
    //unsigned char j;

    //Matriz SCM
    unsigned char *scm = NULL;
    scm = (unsigned char*) malloc(qtd*sizeof(unsigned char));

    if (!scm) {
        puts("Não há memória disponível para gerar a matriz SCM");
        exit(1);
    }

    //Zerar todos os valores na matriz SCM
    //Poderia usar a função calloc(), mas preferi fazer assim
    for (unsigned int p = 0; p < qtd*qtd; p++) {
        *(scm + p) = 0;
    }

    //Preencher a matriz SCM
    for (unsigned int k = 0; k < lin*col; k++) {
       //j = *(m + k); //Coluna
       //i = *(n + k); //Linha
       *((scm + (*(m + k))) + ((*(n + k))*qtd)) += 1;
       //*((scm + j) + (i*qtd)) += 1;
    }

    return scm;
}

unsigned char *quantizar(unsigned char *m, unsigned int lin, unsigned int col, unsigned int lvl)
{
    unsigned char *q = NULL;
    unsigned int k;
    q = (unsigned char *) malloc(lin*col*sizeof(unsigned char));

    if (!q) {
        puts("Não há memória disponível");
        exit(1);
    }

    for (unsigned int i = 0; i < lin*col; i++) {
        k = 1;
        while(k*(NUM_MAXIMO/lvl) < ((*(m + i)))) {
            k++;
        }
        *(q + i) = k-1; //Subtrai 1 porque os valores da matriz quantizada começam em 0
    }

    return q;
}

unsigned char *filtrar_media(unsigned char *m_retorno, unsigned char *m, unsigned int tam_janela, unsigned int lin, unsigned int col)
{
    if (!(tam_janela % 2)) {
        puts("ERRO! O Tamanho da Janela precisa ser Ímpar");
        exit(2);
    }
    unsigned short int s;
    for (int i = 0; i < lin; i++) { //Linha (matriz)
        for (int j = 0; j < col; j++) { //Coluna (matriz)
            s = 0;
            //Fórmula para selecionar um elemento: *((m + j) + (i*col))
            //Para encontrar elementos vizinhos: utilizar (tamanho da janela - 1)/2
            for (int n = 0; n <= ((tam_janela-1)/2); n++) { //Linha (janela)
                for (int k = 0; k <= ((tam_janela-1)/2); k++) { //Coluna (janela)
                    if (!(i + n >= lin)) { //Evitar estouro de memória
                        s += ((j - k) < 0) ? 0 : *((m + j - k) + ((i+n)*col)); //Anteriores
                        if (k) { //Evitar somar o mesmo valor duas vezes
                            s += ((j + k) >= col) ? 0 : *((m + j + k) + ((i+n)*col)); //Pŕoximos
                        }
                    } /*else {
                        s += 0;
                    }*/
                    if (n && !(i - n < 0)) { //Evitar somar a linha central duas vezes e estouro de memória
                            s += ((j - k) < 0) ? 0 : *((m + j - k) + ((i-n)*col)); //Anteriores
                            if (k) { //Evitar somar o mesmo valor duas vezes
                                s += ((j + k) >= col) ? 0 : *((m + j + k) + ((i-n)*col)); //Próximos
                            }
                    } /*else {
                        s += 0;
                    }*/
                }
            }

            //printf("%hhu\n", s);
            *((m_retorno + j) + (i*col)) = (unsigned short int) s/(tam_janela*tam_janela); //Mudar o valor em questão para o valor da média
        }
    }
    return m_retorno;
}