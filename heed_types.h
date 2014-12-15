/*
 * heed_types.h
 */

/* description of realfunc/trigger args */
typedef struct {
    int domain, type, protocol;
} Socket_Args;

typedef struct {
    int sockfd;
    const struct sockaddr *addr;
    socklen_t addrlen;
} Connect_Args;

typedef struct {
    int sockfd;
    const void *buf;
    size_t len;
    int flags;
} Send_Args;

typedef struct {
    int sockfd;
    void *buf;
    size_t len;
    int flags;
} Recv_Args;

/* handlers types defining */
typedef int (*gethostbyname_cb)(const char *);
typedef int (*socket_cb)(Socket_Args *);
typedef int (*connect_cb)(Connect_Args *);
typedef int (*send_cb)(Send_Args *);
typedef int (*recv_cb)(Recv_Args *);