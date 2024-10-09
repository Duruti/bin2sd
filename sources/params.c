#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../includes/params.h"



void GetParametersFromCommandLine(int argc, char **argv, Params *parameter)
{
   // Permet de récuperer les parametres lors du lancement du programme


   //   printf("nb params : %d\nfilename : %s",argc,argv[0]);
   //   argument 0 c'est le nom du programme

   int i=0;
   // on parcours les arguments
   for (i=1 ; i < argc ; i++){
   //   printf("\nargument %d : %s",i,argv[i]);
      i += parseOption(&argv[i],parameter); // si on a parser plusieurs argument on incremente i
   }
}
int parseOption(char **argv,Params *parameter)
{

   int i=0;

	if (argv[i][0]=='-')
   {
      // On test la premiere lettre après le tiret
      switch(argv[i][1])
      {
         case 'b':
         case 'B':
           {
               parameter->filename=argv[++i]; // Récupere le nom du fichier
               strcat(parameter->filename,".bin"); // lui rajoute l'extention bin
               printf("\nSource binary file : %s",parameter->filename);
               break;
           }
         // adresse exec bin
         case 'e':
         case 'E':
            {
               parameter->adressExec = strtol(argv[++i],NULL,16); // atoi(argv[++i]);
               printf("\nAdress exec binary : %2.2X",parameter->adressExec);
               break;
            }
         case 'h':
         case 'H':
            {  
               printf("\n Version %s",Version);
               printf("\n-b name binary file : Permet de charger un fichier binaire");
               printf("\n-e adresse Exec     : Permet de définir l'adresse d'execution du binaire");
               printf("\n-h                  : Info sur les commandes et le programme");
               printf("\n-o name output file : Permet de définir le nom du fichier SD");
               printf("\n-s address Start    : Permet de définir l'adresse de départ du binaire");
               printf("\n");
               break;
            }
         case 'o':
         case 'O':
            {
               parameter->outputFilename = argv[++i];
               strcat(parameter->outputFilename,".sd");
               printf("\nOutput name file : %s",parameter->outputFilename);      
               break;
            }
         // on recupere le nom du fichier de sortie
         // adresse start bin
         case 's':
         case 'S':
            {
               parameter->adressStart = strtol(argv[++i],NULL,16);  // atoi(argv[++i]);
               printf("\nAdress start binary : %2.2X",parameter->adressStart);
               break;
            }
      }
   }
   // else
   // {
   //   if (!parameter->filename) {
	// 		parameter->filename=argv[i];
         
	// 	} else {
	// 		printf("Error\n");
   //       printf("%s\n",parameter->filename);
	// 	}
   // }
   return i;
}