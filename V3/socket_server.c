#include "networking.h"
#include "heads.h"

void process(char *s);
void subserver(int from_client);

int main() {

  int listen_socket,client_socket_0,client_socket_1;
  int f;
  listen_socket = server_setup();

  while (1) {

    client_socket_0=server_connect_init(listen_socket,0);
    printf("first client connected\n");
    //close(listen_socket);
    //listen_socket_1 = server_setup();
    client_socket_1=server_connect_init(listen_socket,1);
    printf("second client connected\n");

    char buffer[100];
    write(client_socket_0,"ready",sizeof(buffer));
    printf("server wrote ready\n");
    read(client_socket_0,buffer,sizeof(buffer));
    write(client_socket_1,buffer,sizeof(buffer));
    close(client_socket_0);
    close(client_socket_1);
  }

  /*while (1) {

    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0)
    subserver(client_socket);
    else
    close(client_socket);
    }*/
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
