#include "actor-router.h"

/*
 * Comportement:
 * 
 */

/**************************************************************************/
void actor_router_func(zsock_t *pipe, void *args)
/**************************************************************************/
{
 zsock_signal(pipe, 0);

 int terminated = 0;
 char* delim = " ";
 char* inter   = (char*)malloc(sizeof(char) * 256);
 char* message = (char*)malloc(sizeof(char) * 256);
 
 char* log_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 char* geohash_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 char* simhash_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 char* command_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 sprintf(log_address, "@tcp://127.0.0.1:%d", PORT_RT_LOG);
 sprintf(geohash_address, "@tcp://127.0.0.1:%d", PORT_RT_GEO);
 sprintf(simhash_address, "@tcp://127.0.0.1:%d", PORT_RT_SIM);
 sprintf(command_address, ">tcp://127.0.0.1:%d", PORT_BOARD);

 zsock_t *log    = zsock_new_push(log_address);
 zsock_t *geo    = zsock_new_push(geohash_address);
 zsock_t *sim    = zsock_new_push(simhash_address);
 zsock_t *reader = zsock_new_pull(command_address);

 while (!terminated)
 {
  /* Attend un message */
  zmsg_t *msg = zmsg_recv(reader);

  /* Si on a un bug pendant la récupération du message,
     l'acteur s'arrête */
  if (!msg)
  {
   message = "Error (router): msg error.\n";
   zstr_send(log, message);
   break;
  }

  /* On récupère la commande dans le message */
  char* command = zmsg_popstr(msg);
  strcpy(inter, command);
  message = strtok(inter, delim);

  /* On agit selon la commande... */
  if (streq(command, "$TERM"))
  {
   zstr_send(geo, "$TERM");
   zstr_send(sim, "$TERM");
   zstr_send(log, "$TERM");
   terminated = 1;
  }
  else if (streq(command, "LIST"))
  {
   zstr_send(log, " Acteur Routeur");
   zstr_send(geo, "LIST"); 
   zstr_send(sim, "LIST"); 
   zstr_send(log, "LIST");
  }
  else if (streq(message, "GEO"))
   zstr_send(geo, command);
  else
  {
   printf("RECV: %s\n", command);
   message = "Error (router): bad command.\n";
   zstr_send(log, message);
  }

  /* On libère la mémoire */
  freen(command);
  zmsg_destroy(&msg);
 } 

 free(inter);
 free(message);
 free(geohash_address);
 free(simhash_address);
 free(log_address);
 free(command_address);
 zsock_destroy(&log);
 zsock_destroy(&geo);
 zsock_destroy(&sim);
 zsock_destroy(&reader);
}