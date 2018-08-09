#include "geohash.h"

#include <stdio.h>

/**************************************************************************/
double interval_mean(struct Interval interval)
/**************************************************************************/
{
 return (interval.max + interval.min) / 2.0;
}

/**************************************************************************/
char* encode_geohash(struct Coord coord, int precision)
/**************************************************************************/
{
 /* Variables */
 struct Interval interval_lat;
 struct Interval interval_long;
 char* hash = (char*)malloc(sizeof(char) * (precision+1));
 int i;
 uint8_t b = 0;
 double mean;
 int even = 1;

 /* On vérifie précision qui doit se trouver entre 1 & 12 max */
 if (precision < 1 || precision > 12)
  precision = 5;

 /* On vérifie que les coordonnées sont dans les bonnes
    bornes de valeur possible */
 if (coord.latitude >= MIN_LAT &&
     coord.latitude <= MAX_LAT &&
     coord.longitude >= MIN_LONG &&
     coord.longitude <= MAX_LONG)
 {
  interval_lat.min = MIN_LAT;
  interval_lat.max = MAX_LAT;
  interval_long.min = MIN_LONG;
  interval_long.max = MAX_LONG;

  for (i = 1 ; i <= 5*precision ; i++)
  {
   /* On décale */
   b <<= 1;

   /* Dans le cas ou i est pair (longitude) */
   if (even)
   {
    /* On vérifie si la valeur est au dessous de la moyenne
       Dans ce cas on met le bit à 1, et on ajuste le borne inf */
    mean = interval_mean(interval_long);
    if (coord.longitude > mean)
    {
     b |= 1;
     interval_long.min = mean;
    }
    /* Sinon on ajuste la borne max */
    else
     interval_long.max = mean;
   }
   /* Dans le cas ou i est impair (latitude) */
   else
   {
    mean = interval_mean(interval_lat);
    if (coord.latitude > mean)
    {
     b |= 1;
     interval_lat.min = mean;
    }
    else
     interval_lat.max = mean;
   }

   /* Si on a terminé pour le char, on reset */
   if (i % 5 == 0)
   {
    hash[(i-1)/5] = base32_to_char[b];
    b = 0x0;
   }

   even = !even;
  }

  hash[precision] = '\0';
  return hash;
 }

 return NULL;
}

/**************************************************************************/
struct Coord decode_geohash(char* hash)
/**************************************************************************/
{
 struct Coord coord;



 return coord;
}
