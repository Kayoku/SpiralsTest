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
 coord.latitude = -25.382708;
 coord.longitude = -49.265506;

 printf("%s\n", encode_geohash(coord, 12));

 return 0;
}
