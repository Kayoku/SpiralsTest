#include "actor-router.h"

/**************************************************************************/
int main()
/**************************************************************************/
{
 printf("Démarrage de l'acteur router.\n");
 zactor_t *actor_router = zactor_new(actor_router_func, "Acteur Routeur");

 printf("Acteur bien démarré.\n");
 zactor_destroy(&actor_router);

 printf("Destruction de l'acteur router.\n");
 return 0;
}
