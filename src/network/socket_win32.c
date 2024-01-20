#include <stdio.h>
#include <errno.h>

#include "defines.h"
#include "core/logger.h"
#include "platform/platform.h"
#include "network/socket.h"

#if PLPPLATFORM_WINDOWS

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdouble-promotion"
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma clang diagnostic pop

//internal prototype
void* getInAddr(struct sockaddr* sa);

struct internalState {
  WSADATA* data;
  SOCKET* socket;
  SOCKADDR_IN6* sockAddrIn;
} state;

i32 socketCreate(platformSocket* platformSocket)
{
  if ((platformSocket->state = platform_allocate(sizeof(struct internalState))) == NULL) {
    PLPFATAL("Error creating plpSocket\n");
  }

  struct internalState* state = (struct internalState*)platformSocket->state;
  state->socket = platform_allocate(sizeof(SOCKET));
  state->data = platform_allocate(sizeof(WSADATA));
  state->sockAddrIn = platform_allocate(sizeof(SOCKADDR_IN6));

  i32 status;
  struct addrinfo* servInfo, *serv;
  struct addrinfo hints;
  platform_zero_memory(&hints, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_STREAM;

  status = WSAStartup(MAKEWORD(2, 2), state->data);

  if (status != 0 ) {
    PLPFATAL("WSAStartup failed with error: [%d] %s", status, gai_strerror(status));
    WSACleanup();
    return -1;
  }

  status = getaddrinfo("::1", "9371", &hints, &servInfo);

  if (status != 0) {
    PLPFATAL("Error while getting addr info: [%d] %s", status, gai_strerror(status));
    WSACleanup();
    return -1;
  }

  SOCKET sockfd = 0;
  b8 found = FALSE;

  for(serv = servInfo; serv != NULL; serv = serv->ai_next) {
    if (serv->ai_family == AF_INET) {
      sockfd = socket(serv->ai_family, serv->ai_socktype, serv->ai_protocol);

      if (sockfd == INVALID_SOCKET) {
        PLPWARN("Socket creation failed");
        perror("client: socket");
        continue;
      }
      found = TRUE;
      break;
    } else if (serv->ai_family == AF_INET6) {
      sockfd = socket(serv->ai_family, serv->ai_socktype, serv->ai_protocol);

      if (sockfd == INVALID_SOCKET) {
        PLPWARN("Socket creation failed");
        perror("client: socket");
        continue;
      }
      found = TRUE;
      break;
    }
  }

  if (found == FALSE) {
    PLPFATAL("Can't find server address");
    return -1;
  }

  if (-1 == sockfd) {
    PLPFATAL("Error while creating the socket");
    perror("socket");
    return -1;
  }

  i32 option = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *) & option, sizeof option);

  status = WSAGetLastError();

  if (status != 0) {
    PLPERR("Setsockopt failed [%d] %s", status, gai_strerror(status));
  }

  status = connect(sockfd, serv->ai_addr, serv->ai_addrlen);
  
  if (status == SOCKET_ERROR) {
    int err = WSAGetLastError();
    PLPERR("Error while connecting the socket: [%d] %s", err, gai_strerror(err));
  }

  char s[INET6_ADDRSTRLEN];
  inet_ntop(serv->ai_family, getInAddr((struct sockaddr *)serv->ai_addr), s, sizeof s);
  PLPTRACE("Connecting to %s", s);

  freeaddrinfo(servInfo);

  *state->socket = sockfd;

  return 0;
}

char* socketReceive(platformSocket* platformSocket)
{
  // listen(plpSocket.socket, 0);

  // status = WSAGetLastError();

  // if (0 != status) {
  //   printf("%s%s", "Error while listening the socket:", gai_strerrorA(status));
  //   return -1;
  // }

  char* recvbuf = platform_allocate(512);
  platform_zero_memory(recvbuf, 512);
  i32 recvbuflen = 512;
  i32 status = 0;

  struct internalState* state = (struct internalState*)platformSocket->state;

  status = recv(*state->socket, recvbuf, recvbuflen, 0);
  if (-1 == status) {
    int err = WSAGetLastError();
    PLPERR("Error while recv: [%d] %s", err, gai_strerror(err));
  } 
  printf("%d bytes received", status);
  printf("%s received", recvbuf);

  return recvbuf;
}

void socketClose(platformSocket* platformSocket)
{
  struct internalState* state = (struct internalState*)platformSocket->state;

  closesocket(*state->socket);
  WSACleanup();
  free(state);
}

void *getInAddr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET) {
      return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

#endif
