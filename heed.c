/*
 * heed.c
 */

#include "heed.h"
#include "realcall_handlers.h"

#define ARR_SIZE 80

static gethostbyname_cb gethostbyname_handlers_array[ARR_SIZE] = {NULL};
static socket_cb socket_handlers_array[ARR_SIZE] = {NULL};
static connect_cb connect_handlers_array[ARR_SIZE] = {NULL};
static send_cb send_handlers_array[ARR_SIZE] = {NULL};
static recv_cb recv_handlers_array[ARR_SIZE] = {NULL};

/* handlers registars block */
int put_gethostbyname_handler(gethostbyname_cb) {
  int i;
  for(i = 0; i < ARR_SIZE; i++)
    if(gethostbyname_handlers_array[i] == NULL) {
      gethostbyname_handlers_array[i] = gethostbyname_cb;
      return 0;
    }

  return -1;
}
int put_socket_handler(socket_cb) {
  int i;
  for(i = 0; i < ARR_SIZE; i++)
    if(socket_handlers_array[i] == NULL) {
      socket_handlers_array[i] = socket_cb;
      return 0;
    }
    
  return -1;
}
int put_connect_handler(connect_cb) {
  int i;
  for(i = 0; i < ARR_SIZE; i++)
    if(connect_handlers_array[i] == NULL) {
      connect_handlers_array[i] = connect_cb;
      return 0;
    }
    
  return -1;
}
int put_send_handler(send_cb) {
  int i;
  for(i = 0; i < ARR_SIZE; i++)
    if(send_handlers_array[i] == NULL) {
      send_handlers_array[i] = send_cb;
      return 0;
    }
    
  return -1;
}
int put_recv_handler(recv_cb) {
  int i;
  for(i = 0; i < ARR_SIZE; i++)
    if(recv_handlers_array[i] == NULL) {
      recv_handlers_array[i] = recv_cb;
      return 0;
    }
    
  return -1;
}

/* triggers block */
/* every trigger runs through all callbacks that registered for its type */
struct hostent * gethostbyname_trigger(const char *name) {
  struct hostent * result;
  
  for(i = 0; i < ARR_SIZE; i++)
    if(socket_handlers_array[i] != NULL)
      socket_handlers_array[i](name); // mb some check how the handler worked
  
  result = gethostbyname_realcall(name);
  // mb calling func that changes the return value
  
  return result;
}
int socket_trigger(int domain_arg, int type_arg, int protocol_arg) {
  int i, result;
  Socket_Args args;
  
  args.domain = domain_arg;
  args.type = type_arg;
  args.protocol = protocol_arg;

  for(i = 0; i < ARR_SIZE; i++)
    if(socket_handlers_array[i] != NULL)
      socket_handlers_array[i](&args); // mb some check how the handler worked
  result = socket_realcall(&args);
  // mb calling func that changes the return value
  
  return result;
}
int connect_trigger(int sockfd_arg, const struct sockaddr *addr_arg, socklen_t addrlen_agr) {
  int i, result;
  Connect_Args args;
  
  args.sockfd = sockfd_arg;
  args.addr = addr_arg;
  args.addrlen = addrlen_agr;
  
  for(i = 0; i < ARR_SIZE; i++)
    if(connect_handlers_array[i] != NULL)
      connect_handlers_array[i](&args); // mb some check how the handler worked
  result = connect_realcall(&args);
  // mb calling func that changes the return value
  
  return result;  
}
int send_trigger(int sockfd_arg, const void *buf_arg, size_t len_arg, int flags_arg) {
  int i, result;
  Send_Args args;
  
  args.sockfd = sockfd_arg;
  args.buf = buf_arg;
  args.len = len_arg;
  args.flags = flags_arg;
  
  for(i = 0; i < ARR_SIZE; i++)
    if(send_handlers_array[i] != NULL)
      send_handlers_array[i](&args); // mb some check how the handler worked
  result = send_realcall(&args);
  // mb calling func that changes the return value
  
  return result;
}
int recv_trigger(int sockfd_arg, void *buf_arg, size_t len_arg, int flags_arg) {
  int i, result;
  Recv_Args args;
  
  args.sockfd = sockfd_arg;
  args.buf = buf_arg;
  args.len = len_arg;
  args.flags = flags_arg;
  
  for(i = 0; i < ARR_SIZE; i++)
    if(recv_handlers_array[i] != NULL)
      recv_handlers_array[i](&args); // mb some check how the handler worked
  result = recv_realcall(&args);
  // mb calling func that changes the return value
  
  return result;
}