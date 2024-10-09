#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>

// #include "../includes/scr.h"
// #include "../includes/files.h"
#include "../includes/params.h"
#include "../includes/files.h"

int main(int nbArg, char **args)
{
   // ****************************
   //     Parametres
   // ****************************


//    int width, height; // width = nb octect height=nb ligne
//    width = 16; //4;
//    height = 30; //16;
//    unsigned char tile[64*128];
 //  char path[50] = "flag.SCR";
//    //                           tiles              cursor,void  border       padlocks          keym,key showm,show 
//   // unsigned char listTiles[] = {8,9,10,11,12,13, 0,0, 14, 7, 0,1,2,3,4,5,6, 17,18,19,20,21,22, 15,16, 23,24};
//    unsigned char listTiles[] = {0,1};
//   // int nbTile=7;


   Params params = {0}; // mets a zero ou nul la structure
   
//    params.width=width;
//    params.height=height;

   GetParametersFromCommandLine(nbArg,args,&params);
   
   // printf("name : %s",params.outputFilename);

   if (params.filename == 0) {
      printf("\nno file");
      return 1;
   }   


   // recupere la taille du fichier binaire
   struct stat fileStat;

    // Obtenir les informations sur le fichier
    if (stat(params.filename, &fileStat) != 0) {
        perror("Erreur lors de l'obtention des informations sur le fichier");
        return 1;
    }

    // Afficher la taille du fichier
    printf("\nLa taille du fichier est : %ld octets\n", fileStat.st_size);
   

//    // gestion fichier
   unsigned char binaryFile[fileStat.st_size];
   
   readBin(params.filename, binaryFile, fileStat.st_size);


   // Affiche le contenu du binaire 
 
   // printf("\nsize array : %d",sizeof(binaryFile));
   // printf("\n");
   // for (int n=0 ; n< sizeof(binaryFile) ; n++){
   //    if (n!=0 && n%8 == 0 ) printf("\n");
   //    printf("%2.2X ",binaryFile[n]);
   // }


   // sauvegarde du sd 
//    int lenghtTiles = sizeof(listTiles) *params.width*params.height;

   char dataSd[1024*512] = {0}; // initialise la SD

   // initialise le label disque
   strcpy(dataSd+500,"VG5000");
   // 506-509 4 octets de libre 

   
   // Remplis la premiere entrée de Fichier
   // 6 Octets = name
   // 2 Octets = N°Fat et 1er Cluster   
   // 1 Octet = Type Caractere (‘B’=basic, ‘M’=code machine, ‘S’=écran)
   // 1 Octet = Taille en cluster

   strcpy(dataSd+0,"TESTSD");
   dataSd[0+6]=0x0;
   dataSd[0+7]=0x01;
   dataSd[0+8]='M';
   dataSd[0+9]=0x01;



   // 510-511 2 octets pour le checksum   

   // calcul le checkSum
   int checkSum = 0;
   for (int i=0 ; i<500 ; i++){
      checkSum += dataSd[i];
   }
   printf("\ncheckSum : %d",checkSum);

   // Ecrire le checksum 
   // Poids fort
   int poidFort = floor(checkSum/256) ;
   int poidFaible = checkSum - (poidFort*256);
   dataSd[511] = poidFort;
   dataSd[510] = poidFaible;
   

   dataSd[512]=0xFF; // Cluster 0 occupé


   // Copy binaire

   dataSd[0x400] = 0x00;
   dataSd[0x401] = 0x50;
   dataSd[0x402] = 0x5B;
   dataSd[0x403] = 0x00;
   dataSd[0x404] = 0x00;
   dataSd[0x405] = 0x00;
   dataSd[0x406] = 0x00;
   dataSd[0x407] = 0x00;
   dataSd[0x408] = 0x00;
   dataSd[0x409] = 0x00;
   dataSd[0x40A] = 0x50;
   dataSd[0x40B] = 0x01;
   dataSd[0x40C] = 0x2F;
   
   for (int i=0 ; i<0x5b+1 ; i++){
      dataSd[0x40D+i] = binaryFile[i];
   }
   
   
   saveSd(params.outputFilename,dataSd,sizeof(dataSd));





// ***********************************************


//    // recupere la 1er tiles en haut a gauche

//    //printf("debut : \n");
   
//    unsigned char *pt = tile;
//    int colum,line;
//    colum = 0 ;
//    line = 0 ;

//    for (int i = 0; i < sizeof(listTiles); i++)
//    {
//       int currentTile = listTiles[i];
//       int nbTileInColum = 200/params.height;
//       colum = currentTile/nbTileInColum;
//       line = currentTile % nbTileInColum;

//       for (int l = 0 ; l < params.height ; l++)
//       {  
//          for (int c = 0 ; c < params.width ; c++)
//          {
//             unsigned char t = cells[(c+colum*params.width) +80*(l+line*params.height)];
//             *pt = t;
//             pt++; 
//          }
//       }
//       //  line++;
//    }
//   // printf("tile : %d\n",tile);
//   // printf("%d\n",sizeof(tile));

//    // sauvegarde le fichier binaire
// //   return 0;

//    char name[50] = "flags.bin"; //"AllTiles.bin";
//    int lenghtTiles = sizeof(listTiles) *params.width*params.height;
//    saveBin(name,tile,lenghtTiles);
// //    //
   return 0;
}
