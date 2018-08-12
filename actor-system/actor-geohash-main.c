#include "actor-geohash.h"

/**************************************************************************/
int main()
/**************************************************************************/
{
 printf("Démarrage de l'acteur geohash.\n");
 zactor_t *actor_geohash = zactor_new(actor_geohash_func, "Acteur GeoHash");

 printf("Acteur bien démarré.\n");
 zactor_destroy(&actor_geohash);

 printf("Destruction de l'acteur geohash.\n");
 return 0;
}
