/*
 * heed.h
 */

#include "heed_types.h"

/* handlers registrars */
int put_gethostbyname_handler(gethostbyname_cb);
int put_socket_handler(socket_cb);
int put_connect_handler(connect_cb);
int put_send_handler(send_cb);
int put_recv_handler(recv_cb);

/* triggers */
/* trigger should get some args for its function and do all callbacks wit this args include realcall */
struct hostent* gethostbyname_trigger(const char *);
int socket_trigger(int, int, int);
int connect_trigger(int, const struct sockaddr *, socklen_t);
int send_trigger(int, const void*, size_t, int);
int recv_trigger(int, void*, size_t, int);