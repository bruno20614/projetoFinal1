#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct pgm {
    int tipo;
    int c;
    int r;
    int mv;
    unsigned char *pData;
};

void viewPGMImage(struct pgm *pio);
void readPGMImage(struct pgm *pio, char *filename);
void writePGMImage(struct pgm *pio, char *filename);