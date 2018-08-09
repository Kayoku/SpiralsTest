#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "geohash.h"

/*
 * Fonction principale
 */

/**************************************************************************/
int main()
/**************************************************************************/
{
 struct Coord coord;
 coord.latitude = 42.6; 
 coord.longitude = -5.6; 

 printf("%s\n", encode_geohash(coord, 5));

 return 0;
}
