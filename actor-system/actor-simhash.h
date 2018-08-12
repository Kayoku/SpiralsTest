#ifndef DEFINE_ACTOR_SIMHASH
#define DEFINE_ACTOR_SIMHASH

#include <stdio.h>
#include <string.h>
#include <czmq.h>

#include "config.h"

/*
 * Fonction
 * Définit le comportement de l'acteur "simhash"
 */

void actor_simhash_func(zsock_t *pipe, void *args);

#endif
