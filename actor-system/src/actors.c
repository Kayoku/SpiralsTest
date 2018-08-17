#include <stdio.h>
#include <stdlib.h>
#include <czmq.h>

#include "utils.h"
#include "actor-router.h"
#include "actor-log.h"
#include "actor-simhash.h"
#include "actor-geohash.h"

int main()
{
 print_sys("Démarrage du système acteur...");

 zactor_t *actor_router  = zactor_new(actor_router_func,  "Acteur Routeur");
 zactor_t *actor_log     = zactor_new(actor_log_func,     "Acteur Log");
 zactor_t *actor_geohash = zactor_new(actor_geohash_func, "Acteur GeoHash"); 
 zactor_t *actor_simhash = zactor_new(actor_simhash_func, "Acteur SimHash");

 print_sys("Acteurs bien démarrés.");

 zactor_destroy(&actor_router);
 zactor_destroy(&actor_log);
 zactor_destroy(&actor_geohash);
 zactor_destroy(&actor_simhash);

 print_sys("Arrêt du système acteur.");

 return 0;
}
