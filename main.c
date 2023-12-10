#include "op_matrizes.h"
#include "pgmlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

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
     int vez=0;
    if(d) {

       while ((dir=readdir(d)) !=NULL) {  
            printf("\n-> %s \n ", dir->d_name);
            if(vez==0||vez==1) continue;
            readPGMImage(&img,dir->d_name);

            //writePGMimage( &img,output);
            
            //char nomeArquivo[256];

filtrar_media snprintf(nomeArquivo,sizeof(nomeArquivo),"BLURRED_%s.pgm",dir->d_name),  dir->d_name,JANELA,  img.r,  img.c;
            
            //snprintf(nomeArquivo,sizeof(nomeArquivo),"BLURRED_%s.pgm",dir->d_name);

            writePGMimage( &img,quantizar(dir->d_name,img.r,img.c,QUANTIZAR));
            writePGMimage( &img,quantizar(dir->d_name,img.r,img.c,QUANTIZAR));

            vez++;
        }
        closedir(d);
    } 


       























    end = clock();
	time_total = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo Total: %lf\n",time_total);  

    return 0;
 }