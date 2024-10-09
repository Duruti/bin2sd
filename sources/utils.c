#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void littleEndian16(int value,char *result){
    printf("\n%2.2X",value);
    int msb = floor(value/256) ; //most significant bit
    int lsb = value - (msb*256); //least significant bit
    result[0] = lsb;
    result[1] = msb;
    printf("\n%2.2X %2.2X",lsb,msb);
}

int checkSumFile(unsigned char *binaryFile,int length){
    int result=0;
    for (int n=0 ; n< length ; n++){
        result += binaryFile[n];
    }
    return result;
}