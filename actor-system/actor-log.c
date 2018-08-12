#include "actor-log.h"

/*
 * Comportement:
 * 
 */

/**************************************************************************/
void actor_log_func(zsock_t *pipe, void *args)
/**************************************************************************/
{
 zsock_signal(pipe, 0);

 int terminated = 0;
 char* message = (char*)malloc(sizeof(char) * 256);

 char* router_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 char* sim_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 char* geo_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 sprintf(router_address, ">tcp://127.0.0.1:%d", PORT_RT_LOG);
 sprintf(sim_address, ">tcp://127.0.0.1:%d", PORT_SIM_LOG);
 sprintf(geo_address, ">tcp://127.0.0.1:%d", PORT_GEO_LOG);
 zsock_t *router = zsock_new_pull(router_address);
 zsock_t *geo = zsock_new_pull(geo_address);
 zsock_t *sim= zsock_new_pull(sim_address);
 zpoller_t *poller = zpoller_new(router, geo, sim, NULL);

 printf("\n============= LOG =============\n\n");

 while (!terminated)
 {
  /* Bloque pour savoir où j'ai reçu un message */
  zsock_t* which = (zsock_t*) zpoller_wait(poller, -1);

  /* Attend un message */
  zmsg_t *msg = zmsg_recv(which);

  /* Si on a un bug pendant la récupération du message,
     l'acteur s'arrête */
  if (!msg)
  {
   printf("Error (log): bad msg.\n");
   break;
  }

  /* On récupère la commande dans le message */
  char* command = zmsg_popstr(msg);


  /* On agit selon la commande... */
  if (streq(command, "$TERM"))
   terminated = 1;
  else if (streq(command, "LIST"))
   printf(" Acteur Log\n");
  else
   printf("%s\n", command);

  /* On libère la mémoire */
  freen(command);
  zmsg_destroy(&msg);
 } 

 free(message);
 free(router_address);
 free(sim_address);
 free(geo_address);
 zpoller_destroy(&poller);
 zsock_destroy(&router); 
 zsock_destroy(&geo); 
 zsock_destroy(&sim); 
}
