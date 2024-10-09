# Bin2SD

Permet de créer un fichier SD pour l'extension VY5040
Plus d'info sur cette extension [vg5000-hardware](https://sites.google.com/view/vg5000-hardware/vg5k-new-hardware/presentation?authuser=0)
Pour cette version :
- Ne permet l'écriture que d'un fichier binaire en langage Machine
- Le nom du binaire dans le SD sera 'A'

## Compilation

Ecrit en C avec GCC
Exemple pour windows 

`gcc sources/*.c -o bin2sd.exe`

## Commande


    -b name binary file : Permet de charger un fichier binaire
    -e adresse Exec     : Permet de définir l'adresse d'execution du binaire
    -h                  : Info sur les commandes et le programme
    -o name output file : Permet de définir le nom du fichier SD
    -s address Start    : Permet de définir l'adresse de départ du binaire

## Exemple

`bin2sd -b desassembler -o DISKB -e 5000 -s 5000`

- Charge le binaire `desassembler.bin`
- Le fichier de sortie sera `DISKB.SD`
- Le programme se chargera en $5000
- Il se lancera en $5000
