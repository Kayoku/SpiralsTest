#include "actor-log.h"

/*
 * Comportement:
 *
 */

////////////////////////////////////////////////////////////////////////////
void actor_log_func(zsock_t *pipe, void *args)
////////////////////////////////////////////////////////////////////////////
{
 zsock_signal(pipe, 0);

 int terminated = 0;
 char reader_address[256];

 sprintf(&reader_address[0], "ipc://127.0.0.1:%d", PORT_LOG);
 zsock_t *reader = zsock_new_sub(reader_address, "LOG");
 zpoller_t *poller = zpoller_new(pipe, reader, NULL);

 while (!terminated)
 {
  zsock_t* which = (zsock_t*) zpoller_wait(poller, -1);
  zmsg_t *msg = zmsg_recv(which);

  if (!msg)
  {
   print_log("Error (log): bad msg.");
   break;
  }

  char* command = zmsg_popstr(msg);

  if (streq(command, "$TERM"))
   terminated = 1;
  else
  {
   char* str = zmsg_popstr(msg);
   if (streq(str, "LIST"))
    print_log(" Acteur Log");
   else
    print_log(str);
  }

  freen(command);
  zmsg_destroy(&msg);
 }

 zpoller_destroy(&poller);
 zsock_destroy(&reader);
}
