#ifndef DEFINE_GEOHASH
#define DEFINE_GEOHASH

#include <stdint.h>
#include <stdlib.h>

#include "Coord.h"

/* https://en.wikipedia.org/wiki/Geohash */

/*
 * Variable permettant de convertir un nombre en char pour geohash
 */

static char base32_to_char[32] = "0123456789bcdefghjkmnpqrstuvwxyz";

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
 */

struct Coord decode_geohash(char* hash);

/*
 * Fonction
 * Permet de décoder une chaine geohash
 * pour retrouver les coordonnées associer
 */

struct Coord decode_geohash(char* hash);

#endif
