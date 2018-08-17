#ifndef DEFINE_GEOHASH_ROUTER
#define DEFINE_GEOHASH_ROUTER

#include <stdio.h>
#include <string.h>
#include <czmq.h>

#include "config.h"
#include "geohash.h"

/*
 * Fonction
 * Définit le comportement de l'acteur "geohash"
 */

void actor_geohash_func(zsock_t *pipe, void *args);

#endif
