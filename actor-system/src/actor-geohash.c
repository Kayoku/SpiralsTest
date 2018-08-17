#include "actor-geohash.h"

/*
 * Comportement:
 * 
 */

////////////////////////////////////////////////////////////////////////////
void actor_geohash_func(zsock_t *pipe, void *args)
////////////////////////////////////////////////////////////////////////////
{
 zsock_signal(pipe, 0);

 int terminated = 0;
 char* delim = " ";
 char* token;
 char message[256] = {0};

 char* router_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 char* log_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 sprintf(log_address, "@tcp://127.0.0.1:%d", PORT_GEO_LOG);
 sprintf(router_address, ">tcp://127.0.0.1:%d", PORT_RT_GEO);

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
   strcpy(message, "Error (geohash): msg error.\n");
   zstr_send(log, message);
   break;
  }

  /* On récupère la commande dans le message */
  char* command = zmsg_popstr(msg);
  strcpy(message, command);
  token = strtok(message, delim);

  /* On agit selon la commande... */
  if (streq(command, "$TERM"))
   terminated = 1;
  else if (streq(command, "LIST"))
   zstr_send(log, " Acteur GeoHash");
  else if (streq(token, "GEO"))
  {
   struct Coord coord;
   int precision;
   token = strtok(NULL, delim);
   coord.latitude = atof(token);
   token = strtok(NULL, delim);
   coord.longitude = atof(token);
   token = strtok(NULL, delim);
   precision = atoi(token);
   char* hash = encode_geohash(coord, precision);
   sprintf(message, "GEO %s", hash);
   zstr_send(log, message);
  }
  else
  {
   strcpy(message, "Error (geohash): bad command.\n");
   zstr_send(log, message);
  }

  /* On libère la mémoire */
  freen(command);
  zmsg_destroy(&msg);
 } 

 free(router_address);
 free(log_address);
 zsock_destroy(&log);
 zsock_destroy(&router); 
}
