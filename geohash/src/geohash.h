#ifndef DEFINE_GEOHASH
#define DEFINE_GEOHASH

#include <stdint.h>
#include <stdlib.h>

/* https://en.wikipedia.org/wiki/Geohash */

/*
 * Variable permettant de convertir un nombre en char pour geohash
 */

static char base32_to_char[33] = "0123456789bcdefghjkmnpqrstuvwxyz";

/*
 * Variables min/max pour la latitude et la longitude
 */

static const int MAX_LAT = 90;
static const int MIN_LAT = -90;

static const int MAX_LONG = 180;
static const int MIN_LONG = -180;


/*
 * Fonction
 * Permet de convertir un caractère (char) en base32 geohash
 */

uint8_t char_to_base32(char c);

/*
 * Structure
 * Définit une intervalle entre deux valeurs
 */

struct Interval
{
 double min;
 double max;
};

/*
 * Structure
 * Définit deux valeurs d'erreur max
 */

struct Coord_Error
{
 double latitude_error;
 double longitude_error;
};

/*
 * Structure
 * Définit une coordonnée par sa latitude et sa longitude
 */

struct Coord
{
 double latitude;
 double longitude;
};

/*
 * Fonction
 * Permet de renvoyer la moyenne de l'intervalle
 */

double interval_mean(struct Interval interval);

/*
 * Fonction
 * Permet d'encoder des coordonnées sous la forme
 * d'une chaine geohash
 *
 * coord: coordonnée qu'on souhaite encoder
 * precision: définit la taille de la chaine en sortie
 */

char* encode_geohash(struct Coord coord, int precision);

/*
 * Fonction
 * Permet de décoder un hash sous la forme de coordonnées
 *
 * hash: hash qu'on veut décoder
 * max_error: valeur max d'erreur sur les coordonnées
 */

struct Coord decode_geohash(const char* hash, struct Coord_Error *max_error);

#endif
