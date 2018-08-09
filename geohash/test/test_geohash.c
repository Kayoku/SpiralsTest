#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"

int main()
{
 CU_pSuite pSuite = NULL;

 /* Initialisation du registre CUnit */
 if (CU_initialize_registry() != CUE_SUCCESS)
  return CU_get_error();

 /* Ajout des suites au registre */
 pSuite = CU_add_suite("Example", NULL, NULL);
 if (pSuite == NULL)
 {
  CU_cleanup_registry();
  return CU_get_error();
 }

 /* Ajout d'un test à une suite */
 if (CU_add_test(pSuite, "first test", fonction) == NULL)
 {
  CU_cleanup_registry();
  return CU_get_error();
 }

 /* Run tous les tests */
 CU_basic_set_mode(CU_BRM_VERBOSE);
 CU_basic_run_tests();
 CU_cleanup_registry();

 return 0;
}
