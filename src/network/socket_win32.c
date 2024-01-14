#include <stdio.h>
#include <errno.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdouble-promotion"
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma clang diagnostic pop

#include "defines.h"

#include "core/logger.h"

#include "network/socket.h"

struct PlpSocket {
  WSADATA data;
  SOCKET *socket;
  SOCKADDR_IN6 sockAddrIn;
};

static struct PlpSocket* plpSocket;

i32 socketCreate()
{
  if ((plpSocket = malloc(sizeof(struct PlpSocket))) == NULL) {
      PLPFATAL("Error creating plpSocket\n");
  }
  if ((plpSocket->socket = malloc(sizeof(SOCKET))) == NULL) {
      PLPFATAL("Error creating plpSocket\n");
  }

  i32 status;
  struct addrinfo* servInfo, *tmp;
  struct addrinfo hints;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;

  status = WSAStartup(MAKEWORD(2, 2), &plpSocket->data);

  if (status != 0 ) {
    PLPFATAL("WSAStartup failed with error: [%d] %s", status, gai_strerror(status));
    WSACleanup();
    return -1;
  }

  status = getaddrinfo(NULL, "9090", &hints, &servInfo);

  if (status != 0) {
    PLPFATAL("Error while getting addr info: [%d] %s", status, gai_strerror(status));
    WSACleanup();
    return -1;
  }

  for(tmp = servInfo; tmp != NULL; tmp = tmp->ai_next) {

    if (tmp->ai_family == AF_INET6) {
      *plpSocket->socket = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);

      if (*plpSocket->socket == -1) {
        PLPWARN("Socket creation failed");
        perror("client: socket");
        continue;
      }
    }
    break;
}

  if (-1 == *plpSocket->socket) {
    PLPFATAL("Error while creating the socket");
    perror("socket");
    return -1;
  }

  i32 option = 1;
  setsockopt(*plpSocket->socket, SOL_SOCKET, SO_REUSEADDR, (char *) & option, sizeof option);

  status = WSAGetLastError();

  if (status != 0) {
    PLPERR("Setsockopt failed [%d] %s", status, gai_strerror(status));
  }

  connect(*plpSocket->socket, servInfo->ai_addr, servInfo->ai_addrlen);

  freeaddrinfo(servInfo);
  status = WSAGetLastError();

  if (0 != status) {
    PLPERR("Error while connecting the socket: [%d] %s", status, gai_strerror(status));
    return -1;
  }

  return 0;
}

char* socketReceive()
{
  // listen(plpSocket.socket, 0);

  // status = WSAGetLastError();

  // if (0 != status) {
  //   printf("%s%s", "Error while listening the socket:", gai_strerrorA(status));
  //   return -1;
  // }

  char* recvbuf = "";
  i32 recvbuflen = 512;
  i32 status = 0;
  
  do {
    status = recv(*plpSocket->socket, recvbuf, recvbuflen, 0);
    if (-1 == status) {
      int err = WSAGetLastError();
      PLPERR("Error while recv: [%d] %s", err, gai_strerror(err));
    } 
    printf("%d bytes received", status);
    printf("%s received", recvbuf);

  } while (status > 0);

  closesocket(*plpSocket->socket);
  WSACleanup();

  return recvbuf;
}

void socketClose()
{
  closesocket(*plpSocket->socket);
  WSACleanup();
  free(plpSocket);
}
