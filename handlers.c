/*
 * handlers.c - basic handlers to be registered and set of realcalls
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h> 
#include "handlers.h"
#include "realcall_handlers.h"

/* basic handlers block */
/* gethostbyname handlers */
int gethostbyname(const char *name) {
  printf("\nGETHOSTBYNAME_ARGS: %s\n", name);

  return 0;
}

/* socket handlers */
int sock_printer(Socket_Args *args) {
  printf("\nSOCK_ARGS: %d\t%d\t%d\n", args->domain, args->type, args->protocol);

  return 0;
}

/* connect handlers */
int connect_printer(Connect_Args *) {

  return 0;
}

/* send handlers */
int send_printer(Send_Args *) {

  return 0;
}

/* recv handlers */
int recv_printer(Recv_Args *) {

  return 0;
}

/* realcall-handlers block */
/* Linux-only realcalls */
struct hostent * gethostbyname_realcall (const char *name) {
  struct hostent * (*real_gethostbyname)(const char *); /* realfunc ptr */
  real_gethostbyname = dlsym(RTLD_NEXT, "gethostbyname");
  
  if(real_gethostbyname)
    return (real_gethostbyname(name));
  else {
    puts("Can't get address of real function");
    return; //// хз, что лучше возвращать в этих местах
  }
}

int socket_realcall (Socket_Args *args) {
  int (*real_socket)(int, int, int);
  real_socket = dlsym(RTLD_NEXT, "socket");
  
  if (real_socket)
    return real_socket(args->domain, args->type, args->protocol);
  else {
    puts("Can't get address of real function");
    return;
  }
}

int connect_realcall (Connect_Args *args) {
  int (*real_connect)(int, const struct sockaddr *, socklen_t);
  real_connect = dlsym(RTLD_NEXT, "connect");
  
  if(real_connect)
    return real_connect(args->sockfd, args->addr, args->addrlen);
  else {
    puts("Can't get address of real function");
    return;
  }
}

int send_realcall (Send_Args *args) {
  int (*real_send)(int, const void*, size_t, int);
  real_send = dlsym(RTLD_NEXT, "send");
  
  if (real_send)
    return real_send(args->sockfd, args->buf, args->len, args->flags);
  else {
    puts("Can't get address of real function");
    return;
  }
}

int recv_realcall (Recv_Args *args) {
  int (*real_recv)(int, void*, size_t, int*);
  real_recv = dlsym(RTLD_NEXT, "recv");
  
  if (real_recv)
    return real_recv(args->sockfd, args->buf, args->len, args->flags);
  else {
    puts("Can't get address of real function");
    return;
  }
}