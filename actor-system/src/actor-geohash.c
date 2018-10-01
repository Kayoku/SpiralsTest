#include "actor-geohash.h"

/*
 * Comportement:
 *
 */

// http://zguide.zeromq.org/page:all
////////////////////////////////////////////////////////////////////////////
void actor_geohash_func(zsock_t *pipe, void *args)
////////////////////////////////////////////////////////////////////////////
{
 zsock_signal(pipe, 0);

 int terminated = 0;
 char* token;
 char inter[256], message[256], router_address[256], log_address[256];

 sprintf(&router_address[0], "ipc://127.0.0.1:%d", PORT_RT);
 sprintf(&log_address[0], "ipc://127.0.0.1:%d", PORT_LOG);

 zsock_t *log    = zsock_new_pub(log_address);
 zsock_t *router = zsock_new_sub(router_address, "GEO");
 zpoller_t *poller = zpoller_new(pipe, router, NULL);

 zsock_t* which;
 while (!terminated)
 {
  which = (zsock_t*) zpoller_wait(poller, -1);

  /* Attend un message */
  zmsg_t *msg = zmsg_recv(which);

  /* Si on a un bug pendant la récupération du message,
     l'acteur s'arrête */
  if (!msg)
  {
   strcpy(message, "Error (geohash): msg error.\n");
   zsock_send(log, "ss", "LOG", message);
   break;
  }

  /* On récupère la commande dans le message */
  char* command = zmsg_popstr(msg);
  command = zmsg_popstr(msg);
  strcpy(inter, command);
  strcpy(command, strtok(inter, " "));

  /* On agit selon la commande... */
  if (streq(command, "$TERM"))
   terminated = 1;
  else if (streq(command, "LIST"))
   zsock_send(log, "ss", "LOG", " Acteur GeoHash");
  else if (streq(command, "GEO"))
  {
   struct Coord coord;
   int precision;
   token = strtok(NULL, " ");
   coord.latitude = atof(token);
   token = strtok(NULL, " ");
   coord.longitude = atof(token);
   token = strtok(NULL, " ");
   precision = atoi(token);
   char* hash = encode_geohash(coord, precision);
   sprintf(message, "GEO %s", hash);
   zsock_send(log, "ss", "LOG", message);
  }
  else
  {
   strcpy(message, "Error (geohash): bad command.\n");
   zsock_send(log, "ss", "LOG",  message);
  }

  /* On libère la mémoire */
  freen(command);
  zmsg_destroy(&msg);
 } 

 zpoller_destroy(&poller);
 zsock_destroy(&router); 
 zsock_destroy(&log);
}
