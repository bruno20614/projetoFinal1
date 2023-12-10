#include "op_matrizes.h"
#include "pgmlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define JANELA 3
#define QUANTIZAR 8
#define FOLDER "./oncotex_pgm"

//adiconar argc e argv
int main(){

    int k;
	clock_t begin, end;
	double time_per_img, time_total = 0;
	long long int a = 999999999;
	begin = clock();

    DIR *d;
    struct dirent *dir;
    d = opendir(FOLDER);

    
     int vez=0;
    if(d) {

       while ((dir=readdir(d)) !=NULL) {  
            vez++;
            //if(vez==4)  break;
            //printf("\n-> %s \n ", dir->d_name);
            puts("0");
            if((vez==1) || (vez==2))  continue;
            puts("01");
            printf("%s",dir->d_name);

            char filename[256];
            snprintf(filename, sizeof(filename), "%s/%s", FOLDER, dir->d_name); 

            struct pgm img;

            readPGMImage(&img,filename);
            struct pgm med;
            med.tipo  = img.tipo;
            med.r = img.r;
            med.c = img.c;
            med.mv =img.mv;
            
            med.pData=NULL;

            med.pData = (unsigned char*) malloc(med.r*med.c*sizeof(unsigned char));
            if(!med.pData){
                puts("sem memória disponível");
                exit(2);
            }
            filtrar_media(med.pData,img.pData,JANELA,img.r,img.c);
            writePGMImage(&med,dir->d_name);
            viewPGMImage(&img);
            viewPGMImage(&med);


            struct pgm mqnt;
            mqnt.tipo = img.tipo;
            mqnt.tipo = img.r;
            mqnt.c = img.c;
            mqnt.mv = (img.mv/QUANTIZAR);
            mqnt.pData = NULL;

            mqnt.pData =(unsigned char *)malloc(mqnt.r * med.c * sizeof(unsigned char));

            if(!mqnt.pData){
                    puts("Sem memória disponível");
                    exit(2);
            }
                    puts("OK");

            mqnt.pData = quantizar(img.pData,img.r,img.c,QUANTIZAR);   


            struct pgm me_qnt;
            me_qnt.tipo = med.tipo;
            me_qnt.tipo = med.r;
            me_qnt.c = med.c;
            me_qnt.mv = (med.mv/QUANTIZAR);
            me_qnt.pData = NULL;

            me_qnt.pData =(unsigned char *)malloc(me_qnt.r * me_qnt.c * sizeof(unsigned char));

            if(!me_qnt.pData){
                    puts("Sem memória disponível");
                    exit(2);
            }
                    puts("OK");

            me_qnt.pData = quantizar(med.pData,med.r,med.c,QUANTIZAR);  
            viewPGMImage(&mqnt);
            viewPGMImage(&me_qnt);
            

        }
        closedir(d);
    } 


       

    end = clock();
	time_total = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo Total: %lf\n",time_total);  

    return 0;
 }