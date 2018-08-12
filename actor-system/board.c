#include <stdio.h>
#include <stdlib.h>
#include <czmq.h>

#include "config.h"

#define SIZE_COMMAND 10
#define SIZE_MESSAGE 50

/**************************************************************************/
void clear_buffer()
/**************************************************************************/
{
 int c = 0;
 while (c != '\n' && c != EOF)
  c = getchar();
}

/**************************************************************************/
int input_read(char* string, int size)
/**************************************************************************/
{
 char *pos = NULL;

 /* Si on lit quelque chose sur l'entrée standard */
 if (fgets(string, size, stdin) != NULL)
 {
  /* on supprime le dernier \n s'il y en a un */
  pos = strchr(string, '\n');
  if (pos != NULL)
   *pos = '\0';
  else
   clear_buffer();

  return 1;
 }
 /* Sinon on nettoie juste le buffer */
 else
  clear_buffer();
 return 0;
}

/**************************************************************************/
int main()
/**************************************************************************/
{
 /* Variables */
 char command[SIZE_COMMAND] = "";
 char message[SIZE_MESSAGE] = "";
 int terminated = 0;

 /* Affichage démarrage */
 printf("Bienvenue dans le plus inutile des systèmes acteur en C!\n");
 printf("Ce système est constitué de 4 acteurs:\n");
 printf("  Acteur Log: Permet d'afficher les logs et les réponses des traitements effectués.\n");
 printf("  Acteur SimHash et Acteur GeoHash: Permet d'utiliser les algos simhash & geohash.\n");
 printf("  Acteur Routeur: Permet à l'utilisateur de communiquer avec le système.\n\n");

 printf("Voici la liste des commandes disponibles: \n");
 printf("\n");

 /* On envoie les messages sur le port */
 char* command_address = (char*)malloc(sizeof(char) * SIZE_ADDRESS + 1);
 sprintf(command_address, "@tcp://127.0.0.1:%d", PORT_BOARD);
 zsock_t *router = zsock_new_push(command_address);

 /******** Zone de commande *********/

 while (!terminated)
 {
  printf("Commande: ");
  fflush(stdout);

  /* On récupère la commande */
  input_read(command, SIZE_COMMAND);

  /* Commande LIST */
  if (strcmp(command, "LIST") == 0)
   zstr_send(router, command);
  /* Commande GEO */
  else if (strcmp(command, "GEO") == 0)
  {
   int precision;
   double latitude, longitude;
   printf("  Latitude: ");
   fflush(stdout);
   input_read(message, SIZE_MESSAGE);
   latitude = atof(message);
   printf("  Longitude: ");
   fflush(stdout);
   input_read(message, SIZE_MESSAGE);
   longitude = atof(message);
   printf("  Precision: ");
   fflush(stdout);
   input_read(message, SIZE_MESSAGE);
   precision = atoi(message);
   sprintf(message, "GEO %lf %lf %d", latitude, longitude, precision);
   zstr_send(router, message);
  }
  /* Commande SIM */
  /*else if (strcmp(command, "SIM") == 0)
  {

  }*/
  /* Commande QUIT */
  else if (strcmp(command, "QUIT") == 0)
  {
   zstr_send(router, "$TERM");
   terminated = 1;
  }
  else
   zstr_send(router, command);
 }

 free(command_address);
 zsock_destroy(&router);
}
