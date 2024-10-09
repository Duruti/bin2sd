#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include <windows.h>

#include "../includes/params.h"
#include "../includes/files.h"
#include "../includes/utils.h"

int main(int nbArg, char **args)
{

   SetConsoleOutputCP(65001);

   Params params = {0}; // mets a zero ou nul la structure

   GetParametersFromCommandLine(nbArg,args,&params);
   
   // printf("name : %s",params.outputFilename);

   if (params.filename == 0) {
      printf("\nNo file");
      return 0;
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
   params.sizeFile = fileStat.st_size;

//    // gestion fichier
   unsigned char binaryFile[params.sizeFile];
   
   readBin(params.filename, binaryFile, params.sizeFile);


   // Affiche le contenu du binaire 
 
   // printf("\nsize array : %d",sizeof(binaryFile));
   // printf("\n");
   // for (int n=0 ; n< sizeof(binaryFile) ; n++){
   //    if (n!=0 && n%8 == 0 ) printf("\n");
   //    printf("%2.2X ",binaryFile[n]);
   // }


   // création du sd 

   char dataSd[1024*512] = {0}; // initialise la SD

   // initialise le label disque
   strcpy(dataSd+500,"VG5000");
   // 506-509 4 octets de libre 

   
   // Remplis la premiere entrée de Fichier
   // 6 Octets = name
   // 2 Octets = N°Fat et 1er Cluster   
   // 1 Octet = Type Caractere (‘B’=basic, ‘M’=code machine, ‘S’=écran)
   // 1 Octet = Taille en cluster

   strcpy(dataSd+0,"A");
   dataSd[0+6]=0x0;
   dataSd[0+7]=0x01; // Ici le départ est le 1er cluster
   dataSd[0+8]='M';

   // Calcul le nombre de cluster pour le fichier
   // 1 Cluster  = 2 secteurs de 512 Octets = 1024
   // Le début du 1er cluster contient un entête de 13 octets 
   
   
   int totalCluster = floor((params.sizeFile - (1024-13))/1024)+1+1;
   printf("\nCluster : %d",totalCluster);
   dataSd[0+9]=totalCluster;



   // 510-511 2 octets pour le checksum   

   // calcul le checkSum, c'est l'addition de tout les octets du secteur repertoire sans le label disque
   
   int checkSum = 0;
   for (int i=0 ; i<500 ; i++){
      checkSum += dataSd[i];
   }
   printf("\ncheckSum : %d",checkSum);

   // Ecrire le checksum
   littleEndian16(checkSum,dataSd+510);

   // int poidFort = floor(checkSum/256) ;
   // int poidFaible = checkSum - (poidFort*256);
   // dataSd[511] = poidFort;
   // dataSd[510] = poidFaible;
   

   // Définition de la talble d'allocation des fichiers 
   dataSd[0x200] = 0xFF; // Cluster 0 occupé
   for (int i=0; i<totalCluster ; i++){
      if (totalCluster==1 && i==0){
         dataSd[0x200+1+i] = 1;
      }else if (i<totalCluster && i!=(totalCluster-1)){
         dataSd[0x200+1+i] = i+2;
      }else if(i!=(totalCluster-1)){
         dataSd[0x200+1+i] = totalCluster; 
      }
   }

   // Copy binaire

   printf("\nAdress Start");
   littleEndian16(params.adressStart,dataSd+0x400);

   printf("\nSize File");
   littleEndian16(params.sizeFile,dataSd+0x402);
   
   dataSd[0x404] = 0x00;
   dataSd[0x405] = 0x00;
   dataSd[0x406] = 0x00;
   dataSd[0x407] = 0x00;
   dataSd[0x408] = 0x00;

   printf("\nAdress Exec");
   littleEndian16(params.adressExec,dataSd+0x409);

   printf("\nChecksum File : %2.2X",checkSumFile(binaryFile,sizeof(binaryFile)));
   littleEndian16(checkSumFile(binaryFile,sizeof(binaryFile)) , dataSd+0x40B );

   // Copie les datas à partir du 1er cluster $400
   int adressCluster = 0x400+13;      

   for (int i=0 ; i<params.sizeFile ; i++){
      dataSd[adressCluster+i] = binaryFile[i];
   }
   
   // Sauvegarde le fichier SD

   saveSd(params.outputFilename,dataSd,sizeof(dataSd));

   return 0;
}
