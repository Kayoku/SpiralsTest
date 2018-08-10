#ifndef DEFINE_SIMHASH
#define DEFINE_SIMHASH

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * Fonction
 * Permet de hasher une chaine de caractère en utilisant
 * la méthode MD5
 *
 * string: chaine en entrée
 * md5:    chaine en sortie (taille (2*MD5_DIGEST_LENGTH+1))
 */

void md5_hash(char* string, char* md5);

/*
 * Fonction
 * Permet d'encoder une chaine de caractère
 * en créant un simhash
 *
 * string:  chaine à encoder
 * block:   nombre de caractère pour chaque hash
 * padding: décalage entre chaque block
 */

uint32_t encode_simhash(char* string, int block, int padding);

/*int hamming_distance(char* string1, char* string2, int block, int padding);*/

#endif
