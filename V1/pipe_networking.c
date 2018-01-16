#include "heads.h"

int server_handshake(int *to_client, int num) {

  int from_client, ret;

  char buffer[HANDSHAKE_BUFFER_SIZE];

  mkfifo(WKP, 0600);

  //block on open, recieve mesage
  printf("[server] handshake: making wkp\n");
  from_client = open(WKP, O_RDONLY, 0);
  read(from_client, buffer, sizeof(buffer));
  printf("[server] handshake: received [%s]\n", buffer);

  sscanf(buffer,"%d",&ret);

  remove(WKP);
  printf("[server] handshake: removed wkp\n");

  //connect to client, send message
  *to_client = open(buffer, O_WRONLY, 0);
  write(*to_client, buffer, sizeof(buffer));

  //read for client
  read(from_client, buffer, sizeof(buffer));
  printf("[server] handshake received: %s\n", buffer);

  if (num) {//second handshake
write(*to_client,"succesfully established connection, connecting to first client",sizeof(buffer));

  }
  else {
    write(*to_client,"succesfully established connection, waiting for second client...",sizeof(buffer));
  }

  //returns integer value of pid of process
  return ret;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *from_server) {

  int to_server;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  //send pp name to server
  printf("[client] handshake: connecting to wkp\n");
  to_server = open( WKP, O_WRONLY, 0);
  if ( to_server == -1 )
    exit(1);

  //make private pipe
  sprintf(buffer, "%d", getpid() );
  mkfifo(buffer, 0600);

  write(to_server, buffer, sizeof(buffer));

  //open and wait for connection
  *from_server = open(buffer, O_RDONLY, 0);
  read(*from_server, buffer, sizeof(buffer));
  /*validate buffer code goes here */
  printf("[client] handshake: received [%s]\n", buffer);

  //remove pp
  printf("buffer: [%s]\n",buffer);
  remove(buffer);
  printf("[client] handshake: removed pp\n");

  //send ACK to server
  write(to_server, ACK, sizeof(buffer));

  //read from server which client you are
  read(*from_server, buffer, sizeof(buffer));
  close(to_server);
  printf("%s\n", buffer);
  if (!strcmp(buffer, "succesfully established connection, waiting for second client...")) {
    return 0; //tells the parent function to write in initial client-client connection
  }
  else {
    return 2; //tells the parent function to read in initial client-client connection
  }
  //return from_server;
}
