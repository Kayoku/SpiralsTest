#include "geohash.h"

#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////
double interval_mean(struct Interval interval)
////////////////////////////////////////////////////////////////////////////
{
 return (interval.max + interval.min) / 2.0;
}

////////////////////////////////////////////////////////////////////////////
uint8_t char_to_base32(char c)
////////////////////////////////////////////////////////////////////////////
{
 uint8_t base32 = 0;

 if (c >= '0' && c <= '9')
  base32 = c - 48;
 else if (c >= 'b' && c <= 'h')
  base32 = c - 88;
 else if (c == 'j' || c == 'k')
  base32 = c - 89;
 else if (c == 'm' || c == 'n')
  base32 = c - 90;
 else if (c >= 'p' && c <= 'z')
  base32 = c - 91;

 return base32;
}

////////////////////////////////////////////////////////////////////////////
char* encode_geohash(struct Coord coord, int precision)
////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////
struct Coord decode_geohash(const char* hash, struct Coord_Error *max_error)
////////////////////////////////////////////////////////////////////////////
{
 /* Variables */
 struct Interval interval_lat = {MIN_LAT, MAX_LAT};
 struct Interval interval_long = {MIN_LONG, MAX_LONG};
 struct Coord coord;
 size_t size_hash = strlen(hash);
 int even = 1;
 int i;
 uint8_t b;
 uint8_t c;
 double mean;

 max_error->latitude_error = MAX_LAT;
 max_error->longitude_error = MAX_LONG;

 /* Pour chaque bits */
 for (i = 0 ; i < size_hash*5 ; i++)
 {
  c = char_to_base32(hash[i/5]);
  b = (c >> (4-(i%5))) & 0x1;

  /* Longitude */
  if (even)
  {
   mean = interval_mean(interval_long);
   if (b)
    interval_long.min = mean;
   else
    interval_long.max = mean;
   max_error->longitude_error /= 2;
  }
  /* Latitude */
  else
  {
   mean = interval_mean(interval_lat);
   if (b)
    interval_lat.min = mean;
   else
    interval_lat.max = mean;
   max_error->latitude_error /= 2;
  }

  even = !even;
 }

 coord.latitude = interval_mean(interval_lat);
 coord.longitude = interval_mean(interval_long);

 return coord;
}
