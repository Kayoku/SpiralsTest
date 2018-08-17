#ifndef DEFINE_ACTOR_LOG
#define DEFINE_ACTOR_LOG

#include <stdio.h>
#include <string.h>
#include <czmq.h>

#include "config.h"
#include "utils.h"

/*
 * Fonction
 * Définit le comportement de l'acteur "log"
 */

void actor_log_func(zsock_t *pipe, void *args);

#endif
