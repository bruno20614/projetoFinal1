#include "op_matrizes.h"
#include "pgmlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define JANELA 3
#define QUANTIZAR 8
//adiconar argc e argv
int main(){

    int k;
	clock_t begin, end;
	double time_per_img, time_total = 0;
	long long int a = 999999999;
	begin = clock();

    DIR *d;
    struct dirent *dir;
    d = opendir("images");

    struct pgm img;
    struct pgm med;
    unsigned int vez=0;

    unsigned char *m_quant = NULL;
    unsigned char *m_quant_media = NULL;
    unsigned char *ma_scm = NULL;

    med.pData = NULL;
    

    if(d) {

       while ((dir=readdir(d)) !=NULL) {  
            vez++;
            printf("\n-> %s \n ", dir->d_name);
            //if (!(strcmp(dir->d_name, ".") || strcmp(dir->d_name, ".."))) continue;
            if (vez == 1 || vez == 2) continue;
            puts("01");
            if (chdir("images") != 0) {
                puts("Não foi possível abrir o diretório");
                exit(2);
            }
            readPGMImage(&img, dir->d_name);
            puts("02");

            med.tipo = img.tipo;
            med.c = img.c;
            med.r = img.r;
            med.mv = img.mv;
            if (!med.pData) {
                med.pData = (unsigned char*) malloc(med.c * med.r * sizeof(unsigned char));
                        
                if (!med.pData) {
                    puts("Não há memória disponível");
                    exit(2);
                }
            }
            puts("OK");
            filtrar_media(med.pData, img.pData, JANELA, img.r, img.c);
            puts("OK_2");
            chdir("..");
            if (chdir("images_blur") != 0) {
                puts("Não foi possível abrir o diretório");
                exit(3);
            }
            writePGMImage(&med, dir->d_name);
            puts("OK_3");
            chdir("..");

            m_quant = quantizar(img.pData, img.r, img.c, QUANTIZAR);
            m_quant_media = quantizar(med.pData, med.r, med.c, QUANTIZAR);
            ma_scm = gerar_matriz_scm(m_quant, m_quant_media, img.r, img.c, 255);

            //free(img.pData);


            //FILE *blurred;
            //blurred fopen("mean.pgm","a");

             //filtrar_media(mean.pgm,readPGMImage(&img,dir->d_name),JANELA,img.r,img.c);           
            //char nomeArquivo[256];

            //filtrar_media(BLUREED.pgm)            
            //snprintf(nomeArquivo,sizeof(nomeArquivo),"BLURRED_%s.pgm",dir->d_name);

            //writePGMimage( &img,quantizar(dir->d_name,img.r,img.c,QUANTIZAR));
            //writePGMimage( &img,quantizar(dir->d_name,img.r,img.c,QUANTIZAR));

            //vez++;
        }
        closedir(d);
    }

    free(med.pData);

            /*readPGMImage(&img,"lena.pgm");

            med.tipo = img.tipo;
            med.c = img.c;
            med.r = img.r;

            med.pData = NULL;
            med.pData = (unsigned char*) malloc(med.c * med.r * sizeof(unsigned char));
            if (!med.pData) {
                puts("Não há memória disponível");
                exit(1);
            }

            puts("OK");
            filtrar_media(med.pData, img.pData, JANELA, img.r, img.c);
            puts("FILTRADA");
            writePGMImage(&med, "lena_BLUR_7x7.pgm");
            puts("IMAGEM CRIADA");

            m_quant = quantizar(img.pData, img.r, img.c, QUANTIZAR);
            m_quant_media = quantizar(med.pData, med.r, med.c, QUANTIZAR);
            ma_scm = gerar_matriz_scm(m_quant, m_quant_media, img.r, img.c, 255); */

       























    end = clock();
	time_total = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo Total: %lf\n",time_total);  

    return 0;
 }