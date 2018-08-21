#include "actor-router.h"

/*
 * Comportement:
 *
 */

////////////////////////////////////////////////////////////////////////////
void actor_router_func(zsock_t *pipe, void *args)
////////////////////////////////////////////////////////////////////////////
{
 zsock_signal(pipe, 0);

 int terminated = 0;
 char writer_address[256], log_address[256], command_address[256];

 char* inter   = (char*)malloc(sizeof(char) * 256);
 char* message = (char*)malloc(sizeof(char) * 256);
 sprintf(&command_address[0], ">tcp://127.0.0.1:%d", PORT_BOARD);
 sprintf(&writer_address[0], "ipc://127.0.0.1:%d", PORT_RT);
 sprintf(&log_address[0], "ipc://127.0.0.1:%d", PORT_LOG);
 zsock_t *reader = zsock_new_pull(command_address);
 zsock_t *writer = zsock_new_pub(writer_address);
 zsock_t *log    = zsock_new_pub(log_address);
 zpoller_t *poller = zpoller_new(pipe, reader, NULL);

 while (!terminated)
 {
  zsock_t* which = (zsock_t*) zpoller_wait(poller, -1);

  /* Attend un message */
  zmsg_t *msg = zmsg_recv(which);

  /* Si on a un bug pendant la récupération du message,
     l'acteur s'arrête */
  if (!msg)
  {
   message = "Error (router): msg error.\n";
   zsock_send(log, "ss", "LOG", message);
   break;
  }

  /* On récupère la commande dans le message */
  char* command = zmsg_popstr(msg);
  strcpy(inter, command);
  message = strtok(inter, " ");

  /* On agit selon la commande... */
  if (streq(command, "$TERM"))
  {
   zsock_send(log, "ss", "LOG", "$TERM");
   terminated = 1;
  }
  else if (streq(command, "LIST"))
  {
   zsock_send(log, "ss", "LOG", "Liste des acteurs en vie:");
   zsock_send(log, "ss", "LOG", " Acteur Routeur");
   zsock_send(log, "ss", "LOG", "LIST");
  }
  //else if (streq(message, "GEO"))
  // zstr_send(geo, command);
  else
  {
   message = "Error (router): bad command.\n";
   zsock_send(log, "ss", "LOG", message);
  }

  /* On libère la mémoire */
  freen(command);
  zmsg_destroy(&msg);
 }

 free(inter);
 free(message);
 zpoller_destroy(&poller);
 zsock_destroy(&log);
 zsock_destroy(&writer);
 zsock_destroy(&reader);
}
