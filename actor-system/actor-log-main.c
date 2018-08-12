#include "actor-log.h"

/**************************************************************************/
int main()
/**************************************************************************/
{
 printf("Démarrage de l'acteur log.\n");
 zactor_t *actor_log= zactor_new(actor_log_func, "Acteur Log");

 printf("Acteur bien démarré.\n");
 zactor_destroy(&actor_log);

 printf("Destruction de l'acteur log.\n");
 return 0;
}

