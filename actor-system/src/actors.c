#include <stdio.h>
#include <stdlib.h>
#include <czmq.h>

#include "utils.h"
#include "actor-router.h"
#include "actor-log.h"
#include "actor-simhash.h"
#include "actor-geohash.h"

/* Structure permettant de gérer
 * l'état du système
 */

struct ActorSystem
{
 int nb_actor;
};

////////////////////////////////////////////////////////////////////////////
zactor_t* new_zactor
////////////////////////////////////////////////////////////////////////////
(
 zactor_fn fn,
 void* name,
 struct ActorSystem* sys
)
{
 sys->nb_actor++;
 return zactor_new(fn, name);
}

////////////////////////////////////////////////////////////////////////////
int remove_from_poller
////////////////////////////////////////////////////////////////////////////
(
 zpoller_t* handler,
 zsock_t* sock,
 struct ActorSystem* sys
)
{
 sys->nb_actor--;
 return zpoller_remove(handler, sock);
}

////////////////////////////////////////////////////////////////////////////
int main()
////////////////////////////////////////////////////////////////////////////
{
 struct ActorSystem sys;
 sys.nb_actor = 0;

 print_sys("Démarrage du système acteur...");

 zactor_t *actor_router =
  new_zactor(actor_router_func, (void*)"Acteur Routeur", &sys);

 zactor_t *actor_log =
  new_zactor(actor_log_func, (void*)"Acteur Log", &sys);

 zactor_t *actor_geohash =
  new_zactor(actor_geohash_func, (void*)"Acteur GeoHash", &sys);

 //zactor_t *actor_simhash = zactor_new(actor_simhash_func, "Acteur SimHash");

 zpoller_t* handler = zpoller_new(actor_router, actor_log,
                                  actor_geohash, NULL);

 print_sys("Acteurs bien démarrés.");

 while (sys.nb_actor > 0)
 {
  zsock_t* sk = (zsock_t*) zpoller_wait(handler, -1);
  if (sk == NULL)
   break;
  remove_from_poller(handler, sk, &sys);
 }

 zpoller_destroy(&handler);
 zactor_destroy(&actor_geohash);
 zactor_destroy(&actor_log);
 zactor_destroy(&actor_router);
 //zactor_destroy(&actor_simhash);

 print_sys("Arrêt du système acteur.");

 return 0;
}
