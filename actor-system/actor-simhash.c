#include "actor-simhash.h"

/*
 * Comportement:
 * 
 */

/**************************************************************************/
void actor_simhash_func(zsock_t *pipe, void *args)
/**************************************************************************/
{
 zsock_signal(pipe, 0);

 int terminated = 0;
 char* message = (char*)malloc(sizeof(char) * 256);
 
 char* router_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 char* log_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 sprintf(log_address, "@tcp://127.0.0.1:%d", PORT_SIM_LOG);
 sprintf(router_address, ">tcp://127.0.0.1:%d", PORT_RT_SIM);

 zsock_t *log    = zsock_new_push(log_address);
 zsock_t *router = zsock_new_pull(router_address);

 while (!terminated)
 {
  /* Attend un message */
  zmsg_t *msg = zmsg_recv(router);

  /* Si on a un bug pendant la récupération du message,
     l'acteur s'arrête */
  if (!msg)
  {
   message = "Error (simhash): msg error.\n";
   zstr_send(log, message);
   break;
  }

  /* On récupère la commande dans le message */
  char* command = zmsg_popstr(msg);

  /* On agit selon la commande... */
  if (streq(command, "$TERM"))
   terminated = 1;
  else if (streq(command, "LIST"))
   zstr_send(log, " Acteur SimHash");
  else
  {
   message = "Error (simhash): bad command.\n";
   zstr_send(log, message);
  }

  /* On libère la mémoire */
  freen(command);
  zmsg_destroy(&msg);
 } 

 free(message);
 free(router_address);
 free(log_address);
 zsock_destroy(&log);
 zsock_destroy(&router); 
}
