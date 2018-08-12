#include "actor-simhash.h"

/**************************************************************************/
int main()
/**************************************************************************/
{
 printf("Démarrage de l'acteur simhash.\n");
 zactor_t *actor_simhash = zactor_new(actor_simhash_func, "Acteur SimHash");

 printf("Destruction de l'acteur simhash.\n");
 zactor_destroy(&actor_simhash);

 printf("Fait.\n");
 return 0;
}
