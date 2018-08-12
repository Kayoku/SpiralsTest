#include "actor-router.h"

/**************************************************************************/
int main()
/**************************************************************************/
{
 printf("Démarrage de l'acteur router.\n");
 zactor_t *actor_router = zactor_new(actor_router_func, "Acteur Routeur");

 printf("Destruction de l'acteur router.\n");
 zactor_destroy(&actor_router);

 printf("Fait.\n");
 return 0;
}
