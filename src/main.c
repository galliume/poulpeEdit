#include <gtk/gtk.h>

#include <stdio.h>
#include <errno.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdouble-promotion"
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma clang diagnostic pop

static void
activate(GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "PoulpeEdit");
  gtk_window_set_default_size(GTK_WINDOW (window), 800, 600);
  gtk_window_present(GTK_WINDOW(window));

  
  GtkWidget *view;
  GtkTextBuffer *buffer;
  char *text = user_data;

  view = gtk_text_view_new();
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (view));
  gtk_text_buffer_set_text(buffer, text, -1);

  gtk_window_set_child (GTK_WINDOW (window), view);
}

int
main(int argc, char **argv)
{
  int status;
  struct addrinfo* servInfo;
  struct addrinfo hints;  
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;

  struct PlpSocket {
    WSADATA data;
    SOCKET socket;
    SOCKADDR_IN6 sockAddrIn;
  } plpSocket;

  status = WSAStartup(MAKEWORD(2, 2), &plpSocket.data);

  if (status != 0 ) {
    printf("%s: %s", "WSAStartup failed with error", gai_strerror(status));
    WSACleanup();
  }

  status = getaddrinfo(NULL, "8289", &hints, &servInfo);

  if (status != 0) {
    printf("%s:%s", "Error while getting addr info", gai_strerror(status));
    WSACleanup();
    return -1;
  }

  plpSocket.socket = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol);

  if (-1 == plpSocket.socket) {
    printf("%s", "Error while creating the socket");
    perror("socket");
    return -1;
  }

  bool option = true;
  setsockopt(plpSocket.socket, SOL_SOCKET, SO_REUSEADDR, (char *) & option, sizeof option);

  status = WSAGetLastError();

  if (status != 0) {
    printf("%s: %s", "setsockopt failed", gai_strerrorA(WSAGetLastError()));
  }

  connect(plpSocket.socket, servInfo->ai_addr, servInfo->ai_addrlen);

  freeaddrinfo(servInfo);
  status = WSAGetLastError();

  if (0 != status) {
    printf("%s%s", "Error while connecting the socket:", gai_strerrorA(status));
    return -1;
  }

  // listen(plpSocket.socket, 0);

  // status = WSAGetLastError();

  // if (0 != status) {
  //   printf("%s%s", "Error while listening the socket:", gai_strerrorA(status));
  //   return -1;
  // }
  
  char recvbuf[512];
  int recvbuflen = 512;

  do {
    status = recv(plpSocket.socket, recvbuf, recvbuflen, 0);
    printf("%d bytes received", status);
    printf("%s received", recvbuf);
  } while (status > 0);

  closesocket(plpSocket.socket);
  WSACleanup();


  GtkApplication *app;
  int gtkStatus;

  app = gtk_application_new("org.galliume", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), recvbuf);
  gtkStatus = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return gtkStatus;
}
