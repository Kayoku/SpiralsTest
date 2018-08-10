#include "simhash.h"

#include <stdio.h>
#include <openssl/md5.h>

/* http://www.yoannsculo.fr/faire-un-hash-md5-dun-string-en-c/ */
/**************************************************************************/
void md5_hash(char* string, char* md5)
/**************************************************************************/
{
 int i;
 char unsigned temp[MD5_DIGEST_LENGTH] = {0};

 MD5((const unsigned char*)string, strlen(string), temp);

 for (i = 0; i < MD5_DIGEST_LENGTH ; i++)
  sprintf(md5 + 2*i, "%02x", temp[i]);
}

/**************************************************************************/
uint32_t encode_simhash(char* string, int block, int padding)
/**************************************************************************/
{
 uint32_t hash = 0;
 uint32_t hash_temp = 0;
 int cpt[32] = {0};
 int size_string = strlen(string);
 int i, j;
 char* block_temp = (char*)malloc(block*sizeof(char)+1);
 char md5_temp[2*MD5_DIGEST_LENGTH+1] = "";
 char md5_temp_32[((2*MD5_DIGEST_LENGTH)/4)+1] = "";

 /* On boucle sur chaque "block" de caractère */
 for (i = 0; i < size_string; i+=padding)
 {
  /* Pour le dernier block, si il dépasse, on
     le prend plus petit */
  if (!(i+block < size_string))
   block -= ((i+block) - size_string) + 1;

  /* Copie le block */
  strncpy(block_temp, &string[i], block);

  /* On hash ce block */
  md5_hash(block_temp, md5_temp);

  /* On prend les 32 premiers bits du hash */
  strncpy(md5_temp_32, md5_temp, 8);

  /* Pour chaque caractère hexadécimal du hash */
  hash_temp = strtol(md5_temp_32, NULL, 16);

  /* On boucle sur chaque bit en incrémentant/décrémentant le cpt */
  for (j = 0; j < 32 ; j++)
   cpt[j] += (hash_temp >> (32-j) & 0x1) ? 1 : -1;
 }

 /* On résout le cpt, si cpt[i] > 0, on met le bit à 1, sinon à 0 */
 for (i = 0 ; i < 32; i++)
 {
  hash <<= 1;
  if (cpt[i] > 0)
   hash |= 1;
 }

 free(block_temp);
 return hash;
}

/**************************************************************************/
int hamming_distance(char* string1, char* string2, int block, int padding)
/**************************************************************************/
{
 uint32_t hash1, hash2, temp;

 hash1 = encode_simhash(string1, block, padding);
 hash2 = encode_simhash(string2, block, padding);

 temp = hash1 ^ hash2;

 return __builtin_popcount(temp);
}
