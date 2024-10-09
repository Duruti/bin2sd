#include <stdio.h>
#include <string.h>
#include <math.h>

//#include "../includes/files.h"

int readBin(char *fileName,unsigned char *data,int sizeData)
{
  if (fileName == 0) return 0;
  printf("load file : %s\n",fileName); 
  
  FILE *file;
  int n;
  unsigned char tempo[sizeData]; 
  unsigned char header[128];
  
  file = fopen(fileName,"rb");
  printf("data\n");
  
  int l = 0; // pour le
  
  // for(int i=0;i<128;i++)
  // {
  //   fread(&header[i],sizeof(char),1,file);
  //   // printf("%2.2x ",header[i]);
  //   l++;
  //   //  if (l%80 == 0 ) printf("\n");
  // }
  
  
  // Lecture des data du SCR

  // printf("Data\n");

  l = 0;
  while (fread(&data[l],sizeof(char),1,file),!feof(file))
  {
   // printf("%2.2X ",data[l]);
    l++;
   // if (l%8 == 0) printf("\n");
  }
  
  fclose(file);

  return 0;
}

void saveSd(char *fileName,unsigned char *data,int length)
{
  printf("\nSize File : %d",length);
  
  printf("\nsave file : %s",fileName); 
  FILE *file;
  int n;


  file = fopen(fileName,"wb");
  for (int i = 0 ; i <length ; i++)
  {
  //  printf("%2.2hhx ",*tiles);
    fwrite(data,sizeof(char),1,file);
    data++;
  }
  fclose(file);
}