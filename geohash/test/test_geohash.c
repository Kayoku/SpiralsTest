#include <stdio.h>
#include <string.h>

#include "geohash.h"

#include "CUnit/Basic.h"

/**************************************************************************/
void test_base32_to_char()
/**************************************************************************/
{
 char* carac[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "b",
                 "c", "d", "e", "f", "g", "h", "j", "k", "m", "n", "p", 
                 "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
 int i;

 for (i = 0 ; i < 32 ; i++)
  CU_ASSERT_EQUAL(base32_to_char(i), carac[i][0]);
}

/**************************************************************************/
void test_encode_geohash()
/**************************************************************************/
{
 /*char* encode_geohash(struct Coord coord, int precision);*/
 int size_test     = 1;
 int i;
 struct Coord coord;

 float latitude[]  = {42.6};
 float longitude[] = {-5.6};
 char* hash[]      = {"ezs42"};

 for (i = 0 ; i < size_test ; i++)
 {
  coord.latitude = latitude[i];
  coord.longitude = longitude[i];
  CU_ASSERT_EQUAL(strcmp(encode_geohash(coord, 5), hash[i]), 0);
 }
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
 pSuite = CU_add_suite("Geohash", NULL, NULL);
 if (pSuite == NULL)
 {
  CU_cleanup_registry();
  return CU_get_error();
 }

 /* Ajout d'un test à une suite */
 if (CU_add_test(pSuite, "base32_to_char", test_base32_to_char) == NULL ||
     CU_add_test(pSuite, "encode_geohash", test_encode_geohash) == NULL)
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
