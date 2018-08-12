#include "actor-geohash.h"

/**************************************************************************/
int main()
/**************************************************************************/
{
 printf("Démarrage de l'acteur geohash.\n");
 zactor_t *actor_geohash = zactor_new(actor_geohash_func, "Acteur GeoHash");

 printf("Destruction de l'acteur geohash.\n");
 zactor_destroy(&actor_geohash);

 printf("Fait.\n");
 return 0;
}
