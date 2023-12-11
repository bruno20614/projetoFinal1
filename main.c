#include "op_matrizes.h"
#include "pgmlib.h"
#include "csvlib.h" 

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define FOLDER "./oncotex_pgm"

//adiconar argc e argv
int main(int argc,char *argv[]) {

    if (argc!=3){
        printf("Formato: \n\t %s <Tamanho da Janela> <Nível de Quantização>\n",argv[0]);
        exit(3);
    }
    char nomeCsv[20] = ("img_");
    strcat(nomeCsv, argv[1]);
    strcat(nomeCsv, argv[2]);
    strcat(nomeCsv, ".csv");

int janela = abs(atoi(argv[1]));
int quant = abs(atoi(argv[2]));     

    int k;
	clock_t begin, end;
	double time_per_img, time_total = 0;
	long long int a = 999999999;
	begin = clock();

    DIR *d;
    struct dirent *dir;
    d = opendir(FOLDER);
        
    gerar_csv( quant, nomeCsv);
    
    int vez=0;
    if(d) {

       while ((dir=readdir(d)) != NULL) {  
            vez++;                        
            
            if((vez==1) || (vez==2))  continue; // Ignorar o "." e ".."
            
            //printf("%s",dir->d_name);

            char filename[300];
            snprintf(filename, sizeof(filename), "%s/%s", FOLDER, dir->d_name); 

            struct pgm img;

            readPGMImage(&img,filename);
            
            struct pgm med;
            med.tipo  = img.tipo;
            med.r = img.r;
            med.c = img.c;
            med.mv =img.mv;            
            med.pData=NULL;

            med.pData = (unsigned char*) malloc(med.r * med.c * sizeof(unsigned char));
            
            if (!(med.pData)) {
                puts("[ERRO] Não há memória disponível.");
                exit(2);
            }

            if (chdir("output") != 0) {
                perror("Erro ao abrir o diretório");
            }

            filtrar_media(med.pData, img.pData, janela, img.r, img.c);
            writePGMImage(&med, dir->d_name);
            
            //viewPGMImage(&img);
            //viewPGMImage(&med);

            chdir("..");

            struct pgm mqnt;
            mqnt.tipo = img.tipo;
            mqnt.r = img.r;
            mqnt.c = img.c;
            mqnt.mv = (img.mv/quant);
            mqnt.pData = NULL;

            mqnt.pData =(unsigned char *) malloc(mqnt.r * med.c * sizeof(unsigned char));

            if (!(mqnt.pData)) {
                puts("[ERRO] Não há memória disponível.");
                exit(2);
            }                    

            mqnt.pData = quantizar(img.pData, img.r, img.c, quant);

            struct pgm me_qnt;
            me_qnt.tipo = med.tipo;
            me_qnt.r = med.r;
            me_qnt.c = med.c;
            me_qnt.mv = (med.mv/quant);
            me_qnt.pData = NULL;

            me_qnt.pData = (unsigned char *) malloc(me_qnt.r * me_qnt.c * sizeof(unsigned char));

            if (!(me_qnt.pData)) {
                puts("[ERRO] Não há memória disponível.");
                exit(2);
            }
                    
            me_qnt.pData = quantizar(med.pData,med.r,med.c,quant);  
            
            //viewPGMImage(&mqnt);
            //viewPGMImage(&me_qnt);            

            struct pgm scm;
            scm.tipo = img.tipo;
            scm.r = quant;
            scm.c = quant;
            scm.mv = quant;

            scm.pData = gerar_matriz_scm(mqnt.pData, me_qnt.pData, scm.r, scm.c, quant);

            //viewPGMImage(&scm);

            FILE *rev;
            rev = fopen("ordem_imagens.txt", "a+");
            if (!(rev)) {
                puts("[Erro] Falha na abertura do arquivo.");
                exit(1);
            }

            fprintf(rev, "%s\n", dir->d_name);
            fclose(rev);

            char *rotulo = strtok(dir->d_name, "_");
            //puts("01");
            //printf("%s\n", rotulo);

            preencher_csv(scm.pData, quant, nomeCsv, atoi(rotulo));

            //puts("02");
        }
        closedir(d);
    } 

    end = clock();
	time_total = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo Total: %lf\n",time_total);  

    return 0;
}