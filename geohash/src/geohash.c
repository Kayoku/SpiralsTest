#include "geohash.h"

#include <stdio.h>

/**************************************************************************/
float interval_mean(struct Interval interval)
/**************************************************************************/
{
 return (interval.max + interval.min) / 2.0;
}

/**************************************************************************/
char base32_to_char(uint8_t b)
/**************************************************************************/
{
 char c = 48;

 /* Entre 0-9 */
 if (b < 10)
  c += b;
 /* Pour a-z excluant a,i,l,o */
 else
 {
  /* i */
  if (b < 17)
   c += 40 + b;
  /* l */
  else if (b < 19)
   c += 41 + b;
  /* o */
  else if (b < 21)
   c += 42 + b;
  /* ... z */
  else
   c += 43 + b;
 }

 return c;
}

/**************************************************************************/
char* encode_geohash(struct Coord coord, int precision)
/**************************************************************************/
{
 /* Variables */
 struct Interval interval_lat;
 struct Interval interval_long;
 char* hash = (char*)malloc(sizeof(char) * (precision+1));
 int i, j;
 uint32_t bin_lat = 0x0, bin_long = 0x0;
 uint8_t b;
 int pos = -1;

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

  for (i = 0 ; i < 5*precision ; i++)
  {
   /* Dans le cas ou i est pair (longitude) */
   if (i % 2 == 0) 
   {
    /* on décale */
    bin_long <<= 1; 

    /* On vérifie si la valeur est au dessous de la moyenne
       Dans ce cas on met le bit à 1, et on ajuste le borne inf */
    if (coord.longitude > interval_mean(interval_long))
    {
     bin_long |= 1; 
     interval_long.min = interval_mean(interval_long);
    }
    /* Sinon on ajuste la borne max */
    else
     interval_long.max = interval_mean(interval_long);
   }
   /* Dans le cas ou i est impair (latitude) */
   else
   {
    bin_lat <<= 1; 
    if (coord.latitude > interval_mean(interval_lat))
    {
     bin_lat |= 1;
     interval_lat.min = interval_mean(interval_lat);
    }
    else
     interval_lat.max = interval_mean(interval_lat);
   }
  }

  /* Maintenant qu'on a les bin_lat & bin_long,
     on va recréer les caractères */
  for (i = precision-1 ; i >= 0 ; i--)
  {
   b = 0x00;
   pos++;

   for (j = 4 ; j >= 0 ; j--)
   {
    /* Si c'est pair (longitude) */
    b <<= 1;
    if ((j+i) % 2 == 0)
     b |= (bin_long >> (int)(i*5+j)/2) & 0x1;
    /* Si c'est impair (latitude) */
    else
     b |= (bin_lat >> (int)(i*5+j)/2) & 0x1;
   }

   /* Ici on initialise un nouveau caractère à chaque nouveau 5 bits */
   hash[pos] = base32_to_char(b);
  }

  return hash;
 }

 return NULL;
}

/**************************************************************************/
/*struct Coord decode_geohash(char* geohash)*/
/**************************************************************************/
/*{
 return NULL;
}*/
