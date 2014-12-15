/*
 * handlers.h - header wit basic handlers prototypes
 */

#include "heed_types.c"

int gethostbyname_printer(const char *);

int sock_printer(Socket_Args *);

int connect_printer(Connect_Args *);

int send_printer(Send_Args *);

int recv_printer(Recv_Args *);