#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <openssl/md5.h>

#include "CUnit/Basic.h"

#include "simhash.h"

/**************************************************************************/
void test_md5_hash()
/**************************************************************************/
{
 char* strings[] = {"premier test",
                   "ceci est une longue phrase",
                   "Voila un nouveau hash",
                   "blablablabla"};
 char* hashs[]  = {"6598609863c7f869be3347ef3f91aa62",
                   "09abd41e19959d87956d9712706d7e3c",
                   "3d751b36ca259c45f90b9d38e08b9f7c",
                   "5993d7a73d9f9a694e411ba0788cfe2d"};

 int size = 4, i;
 char md5_temp[2*MD5_DIGEST_LENGTH+1] = "";

 for (i = 0; i < size ; i++)
 {
  memset(md5_temp, 0, MD5_DIGEST_LENGTH);
  md5_hash(strings[i], md5_temp);
  CU_ASSERT_TRUE(strcmp(md5_temp, hashs[i]) == 0);
 }
}

/**************************************************************************/
void test_hamming_distance()
/**************************************************************************/
{
 char* string = "Je suis une phrase de test pour voir si cela marche";
 char* string2 = "Je suis une phrase de test pour voir si cela marche";
 char* string3 = "Phrase totalement différente";

 CU_ASSERT_TRUE(hamming_distance(string, string2, 2, 1) == 0);
 CU_ASSERT_FALSE(hamming_distance(string, string3, 2, 1) == 0);
}

/**************************************************************************/
int main()
/**************************************************************************/
{
 CU_pSuite pSuite = NULL;

 /* Initialisation du registre CUnit */
 if (CU_initialize_registry() != CUE_SUCCESS)
  return CU_get_error();

 /* Ajout des suites au registre */
 pSuite = CU_add_suite("SimHash", NULL, NULL);
 if (pSuite == NULL)
 {
  CU_cleanup_registry();
  return CU_get_error();
 }

 /* Ajout d'un test à une suite */
 if (CU_add_test(pSuite, "md5_hash", test_md5_hash) == NULL ||
     CU_add_test(pSuite, "hamming_distance", test_hamming_distance) == NULL)
 {
  CU_cleanup_registry();
  return CU_get_error();
 }

 /* Run tous les tests */
 CU_basic_set_mode(CU_BRM_VERBOSE);
 CU_set_error_action(CUEA_FAIL);
 CU_basic_run_tests();
 CU_cleanup_registry();

 return 0;
}
