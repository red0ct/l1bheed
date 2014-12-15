/*
 * realcall_handlers.h
 */

#include "heed_types.h"

struct hostent* gethostbyname_realcall (const char *);

int socket_realcall (Socket_Args *);

int connect_realcall (Connect_Args *);

int send_realcall (Send_Args *);

int recv_realcall (Recv_Args *);