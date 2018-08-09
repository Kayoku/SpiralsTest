#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>

#include "geohash.h"

/*
 * Fonction décrivant la façon d'utiliser la fonction
 */

/**************************************************************************/
void print_usage()
/**************************************************************************/
{
 printf("Usage: ./geohash --action decode --hash <hash>\n       ./geohash --action encode --precision <p> --latitude <lat> --longitude <long>\n<hash>: 1 - 12 characters.\n<lat>: -90..+90\n<long>: -180..+180\n<p>: 1 - 12\n");
 exit(EXIT_FAILURE);
}

/*
 * Fonction principale
 */

/**************************************************************************/
int main(int argc, char *argv[])
/**************************************************************************/
{
 int opt = 0;
 int action = 0;
 char* hash = (char*)malloc(sizeof(char) * 13);
 double latitude = 1000., longitude = 1000.;
 int precision = 0;
 int long_index = 0;
 struct Coord_Error max_error;
 struct Coord coord;

 /* On récupère les arguments */

 static struct option long_options[] =
 {
  {"action",    required_argument, 0, 'a'},
  {"hash",      required_argument, 0, 'h'},
  {"latitude",  required_argument, 0, 'l'},
  {"longitude", required_argument, 0, 'o'},
  {"precision", required_argument, 0, 'p'}
 };

 while ((opt = getopt_long_only(argc, argv, "",
                long_options, &long_index)) != -1)
 {
  switch(opt)
  {
   case 'a':
    if (strcmp(optarg, "encode") == 0)
     action = 1;
    else if (strcmp(optarg, "decode") == 0)
     action = 2;
    break;
   case 'h':
    strcpy(hash, optarg);
    break;
   case 'l':
    latitude = atof(optarg);
    break;
   case 'o':
    longitude = atof(optarg);
    break;
   case 'p':
    precision = atoi(optarg);
    break;
   default:
    print_usage();
  }
 }

 /* On check certaines conditions d'arrêt */
 if (!action ||
     (action == 1 && (latitude == 1000. || longitude == 1000.)) ||
     (action == 2 && (strlen(hash) == 0 || strlen(hash) > 12)) ||
     (action == 1 && (precision < 0 || precision > 12)))
  print_usage();

 /* On exécute le traitement voulu */
 if (action == 1)
 {
  coord.latitude = latitude;
  coord.longitude = longitude;
  printf("Encodage geohash des coordonnées suivantes: \n");
  printf("  latitude:  %lf\n", coord.latitude);
  printf("  longitude: %lf\n", coord.longitude);
  printf("Avec une précision de %d caractères.\n\n", precision);
  printf("Résultat: %s\n", encode_geohash(coord, precision));
 }
 else if (action == 2)
 {
  coord = decode_geohash(hash, &max_error);
  printf("Decodage du geohash suivant: \n");
  printf("  hash: %s\n\n", hash);
  printf("Résultat: \n");
  printf("  latitude: %lf +- %lf\n", coord.latitude,
                                     max_error.latitude_error);
  printf("  longitude: %lf +- %lf\n", coord.longitude,
                                      max_error.longitude_error);
 }

 return 0;
}
