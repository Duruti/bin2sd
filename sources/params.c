#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../includes/params.h"



void GetParametersFromCommandLine(int argc, char **argv, Params *parameter)
{
//   printf("nb params : %d\nfilename : %s",argc,argv[0]);
   // argument 0 c'est le nom du programme

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
            parameter->filename=argv[++i]; // Récupere le non du fichier
            strcat(parameter->filename,".bin"); // lui rajoute l'extention bin
            printf("\nSource binary file : %s",parameter->filename);
            
            break;
           }
         // adresse exec bin
         case 'e':
         case 'E':
            parameter->adressExec = atoi(argv[++i]);
            printf("\nAdress exec binary : %d",parameter->adressExec);
            break;

         case 'i':
         case 'I':
         // test le mot
            if (strcmp(argv[i],"-info") == 0) 
            {
               printf("\n Version %s",Version);
            }
            break;
         // case 'H':
         // case 'h':
         //    if ( (strcmp(argv[i],"-height") == 0) || (strcmp(argv[i],"-HEIGHT") == 0) || (strcmp(argv[i],"-h") == 0) || (strcmp(argv[i],"-H") == 0)) 
         //    {
         //       int v = atoi(argv[++i]);
         //       printf("Height : %d \n",v);
         //    }
         //    break;

         // case 'W':
         // case 'w':
         //    if ( (strcmp(argv[i],"-width") == 0) || (strcmp(argv[i],"-WIDTH") == 0) || (strcmp(argv[i],"-w") == 0) || (strcmp(argv[i],"-W") == 0))
         //    {
         //       int v = atoi(argv[++i]);
         //       printf("width : %d \n",v);
         //    }
         //    break;
         // case 't':
         // case 'T':
         //    if ( (strcmp(argv[i],"-table") == 0) || (strcmp(argv[i],"-TABLE") == 0) || (strcmp(argv[i],"-t") == 0) || (strcmp(argv[i],"-T") == 0))
         //    {
         //       // int c;
         //       printf("\nTable : ");
               
         //       // do
         //       //    {
         //       //    printf("%d\n",i);
                  
         //       //int v = atoi(argv[i]);
         //       char *s = argv[i];
         //       printf("%s\n",s);
         //       //v = atoi(argv[++i]);
         //      //; printf("%d\n",v);
                  
         //       //    printf("%d",v);
         //       //    c = *argv[i];
         //       //    printf("\n%s",c);
                  
         //       //    if (c==',') i=i+2;
         //       //    }
         //       //    while (c ==',');
         //    }
         //    break;
         

         case 'o':
         case 'O':
            parameter->outputFilename = argv[++i];
            strcat(parameter->outputFilename,".sd");
            printf("\nOutput name file : %s",parameter->outputFilename);      
            break;
         // on recupere le nom du fichier de sortie
         // adresse start bin
         case 's':
         case 'S':
            parameter->adressStart = atoi(argv[++i]);
            printf("\nAdress exec binary : %d",parameter->adressStart);
            break;

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