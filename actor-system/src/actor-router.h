#ifndef DEFINE_ACTOR_ROUTER
#define DEFINE_ACTOR_ROUTER

#include <stdio.h>
#include <string.h>
#include <czmq.h>

#include "config.h"

/*
 * Fonction
 * Définit le comportement de l'acteur "routeur"
 */

void actor_router_func(zsock_t *pipe, void *args);

#endif
