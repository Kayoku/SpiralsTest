#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>

#include "simhash.h"

/*
 * Fonction décrivant la façon d'utiliser la fonction
 */

/**************************************************************************/
void print_usage()
/**************************************************************************/
{
 printf("Usage: ./simhash --action hash --block <b> --padding <p> --input <string>\n       ./simhash --action hamming --block <b> --padding <p> --input <string> --input2 <string>\n<string>: chaine de caractère. (max 256)\n<b>: taille des blocks à découpé pour les hashs. (defaut: 2)\n<p>: décalage entre chaque hash. (defaut: 1)\n");
 exit(EXIT_FAILURE);
}

/*
 * Fonction principale
 */

/**************************************************************************/
int main(int argc, char *argv[])
/**************************************************************************/
{
 int opt = 0;
 int action = 0;
 int block = 2;
 int padding = 1;
 char* input = (char*)malloc(sizeof(char) * 256 + 1);
 char* input2 = (char*)malloc(sizeof(char) * 256 + 1);
 int long_index = 0;

 /* On récupère les arguments */

 static struct option long_options[] =
 {
  {"action",    required_argument, 0, 'a'},
  {"input",     required_argument, 0, 'i'},
  {"input2",    required_argument, 0, 'l'},
  {"block",     required_argument, 0, 'b'},
  {"padding",   required_argument, 0, 'p'}
 };

 while ((opt = getopt_long_only(argc, argv, "",
                long_options, &long_index)) != -1)
 {
  switch(opt)
  {
   case 'a':
    if (strcmp(optarg, "hash") == 0)
     action = 1;
    else if (strcmp(optarg, "hamming") == 0)
     action = 2;
    break;
   case 'i':
    strcpy(input, optarg);
    break;
   case 'l':
    strcpy(input2, optarg);
    break;
   case 'b':
    block = atoi(optarg); 
    break;
   case 'p':
    padding = atoi(optarg);
    break;
   default:
    print_usage();
  }
 }

 /* On check certaines conditions d'arrêt */
 if (!action)
  print_usage();

 /* On exécute le traitement voulu */
 if (action == 1)
 {
  printf("Hash de la chaine suivante avec simhash: \n");
  printf("  input: %s\n", input);
  printf("Résultat: %u\n", encode_simhash(input, block, padding));
 }
 else if (action == 2)
 {
  printf("Distance de hamming entre les deux entrées suivantes: \n");
  printf("  input1: %s\n", input);
  printf("  input2: %s\n", input2);
  printf("Résultat: %d\n", hamming_distance(input, input2, block, padding));
 }

 free(input);
 free(input2);
 return 0;
}
