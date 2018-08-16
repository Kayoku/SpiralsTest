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

void md5_hash(const char* string, char* md5);

/*
 * Fonction
 * Permet d'encoder une chaine de caractère
 * en créant un simhash
 *
 * string:  chaine à encoder
 * block:   nombre de caractère pour chaque hash
 * padding: décalage entre chaque block
 */

uint32_t encode_simhash(const char* string, int block, int padding);

/*
 * Fonction
 * Permet d'encoder deux chaines de caractères
 * avec l'algorithme simhash puis
 * de calculer la distance de hamming entre les deux
 *
 * string1: première chaine
 * string2: seconde chaine
 * block:   nombre de caractère pour chaque hash
 * padding: décalage entre chaque block
 */

int hamming_distance(const char* string1,
                     const char* string2,
                     int block,
                     int padding);

#endif
