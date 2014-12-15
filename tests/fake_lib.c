#include "heed.h"
#include "handlers.h"

/* some special handlers code */

/* registations of callbacks */
/*** here user should reg needed std and mb some special handlers ***/

put_gethostbyname_handler(gethostbyname_printer);

put_socket_handler(sock_printer);

/* functions-fakes with calls of triggers */

struct hostent *gethostbyname(const char *name) {
  return gethostbyname_trigger(name);
}

int socket(int domain, int type, int protocol) {
  return socket_trigger(domain, type, protocol);
}

// and so on
/* ... */