#define Version "v0.00.1\n"

typedef struct s_parameter
{
   char *filename;
   char *outputFilename;
   int adressStart;
   int adressExec;
   int sizeFile;

} Params;

int parseOption(char **argv, struct s_parameter *parameter);
void GetParametersFromCommandLine(int argc, char **argv, Params *parameter);