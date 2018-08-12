#include "actor-simhash.h"

/**************************************************************************/
int main()
/**************************************************************************/
{
 printf("Démarrage de l'acteur simhash.\n");
 zactor_t *actor_simhash = zactor_new(actor_simhash_func, "Acteur SimHash");

 printf("Acteur bien démarré.\n");
 zactor_destroy(&actor_simhash);

 printf("Destruction de l'acteur simhash.\n");
 return 0;
}
