# Bin2SD

Permet de créer un fichier SD pour l'extension VY5040.
Pour cette version, ne permet que l'ecriture d'un fichier binaire en langage Machine sur un cluster

## Compilation

Ecrit en C avec GCC

`gcc sources/*.c -o bin2sd.exe`

## Commande


    -b binary file      : Permet de charger un fichier binaire
    -e adresse Exec     : Permet de définir l'adresse d'execution du binaire
    -h                  : Info sur les commandes et le programme
    -o output file      : Permet de définir le nom du fichier SD
    -s address Start    : Permet de définir l'adresse de départ du binaire

