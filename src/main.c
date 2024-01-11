#include <gtk/gtk.h>

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
}

int
main(int argc, char **argv)
{
  struct PlpSocket {
    WSADATA data;
    SOCKET socket;
    SOCKADDR_IN sockAddrIn;
  } plpSocket;

  WSAStartup(MAKEWORD(2, 2), &plpSocket.data);

  plpSocket.socket = socket(AF_INET, SOCK_STREAM, 0);

  if (INVALID_SOCKET == plpSocket.socket) {
    printf("%s", "Error while creating the socket");
    return -1;
  }

  bool option = false;
  int optionLen = sizeof (bool);
  setsockopt(plpSocket.socket, SOL_SOCKET, SO_REUSEADDR, (char *) & option, optionLen);

  inet_pton(AF_INET, "127.0.0.1", & plpSocket.sockAddrIn.sin_addr.s_addr);
  plpSocket.sockAddrIn.sin_family = AF_INET;
  plpSocket.sockAddrIn.sin_port = htons(8289);
  bind(plpSocket.socket, (SOCKADDR*)&plpSocket.sockAddrIn, sizeof(plpSocket.sockAddrIn));

  int status = WSAGetLastError();

  if (0 != status) {
    printf("%s%d", "Error while binding the socket:", status);
    return -1;
  }

  connect(plpSocket.socket, (SOCKADDR*) & plpSocket.sockAddrIn, sizeof(plpSocket.sockAddrIn));

  status = WSAGetLastError();

  if (0 != status) {
    printf("%s%d", "Error while connecting the socket:", status);
    return -1;
  }

  listen(plpSocket.socket, 0);

  status = WSAGetLastError();

  if (0 != status) {
    printf("%s%d", "Error while listening the socket:", status);
    return -1;
  }
  
  char recvbuf[512];
  int recvbuflen = 512;

  do {
    status = recv(plpSocket.socket, recvbuf, recvbuflen, 0);
    printf("%d bytes received {}", status);
    printf("%s received {}", recvbuf);
  } while (status > 0);

  closesocket(plpSocket.socket);
  WSACleanup();

  GtkApplication *app;
  int gtkStatus;

  app = gtk_application_new("org.galliume", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  gtkStatus = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return gtkStatus;
}
