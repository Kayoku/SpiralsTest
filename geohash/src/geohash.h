#ifndef DEFINE_GEOHASH
#define DEFINE_GEOHASH

#include <stdint.h>
#include <stdlib.h>

#include "Coord.h"

/* https://en.wikipedia.org/wiki/Geohash */

/*
 * Structure
 * Définit une intervalle entre deux valeurs
 */

struct Interval
{
 float min;
 float max;
};

/*
 * Fonction
 * Permet de renvoyer la moyenne de l'intervalle
 */

float interval_mean(struct Interval interval);

/*
 * Fonction
 * Permet de renvoyer une valeur base32 en char selon
 * le codage geohash
 */

char base32_to_char(uint8_t b);

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
 * Permet de décoder une chaine geohash
 * pour retrouver les coordonnées associer
 */

struct Coord decode_geohash(char* hash);

#endif
