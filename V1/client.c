#include "heads.h"

/*int establish_connection_client(int * to_server, int * from_server) {

  char my_pipe[100];
  
  //fd1 = open(my_pipe, O_RDONLY);
  printf("[client] opening WKP\n");
  *to_server = open(WKP, O_WRONLY);

  sprintf(my_pipe, "%d", getpid());
  mkfifo(my_pipe, 0600);

  
  write(*to_server, my_pipe, sizeof(my_pipe));
  printf("[client] opening my pipe\n");
  *from_server=open(my_pipe,O_RDONLY, 0);
  
  //char conf_rec[100];
  read(*from_server, my_pipe, 100);
  remove(my_pipe);
  //char conf_send[100] = "confirmation recieved";
  write(*to_server, "confirmation received", 100);
  //char status[100];
  printf("[client] wrote confirmation\n");

  //tells client if it is first or second
  read(*from_server, my_pipe, 100);
  close(*to_server);
  printf("%s\n", my_pipe);
  if (!strcmp(my_pipe, "succesfully established connection, waiting for second client...")) {
    return 0; //tells the parent function to write in initial client-client connection
  }
  else {
    return 1; //tells the parent function to read in initial client-client connection
  }
  //INCOMPLETE NEEDS TO BE FINISHED AND DEBUGGED
  }*/







int main() {

  int which_client;
  int from_server;
  int up, down;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  which_client=client_handshake( &from_server );

  if (which_client)
    { //yes is the second client, no is the first
    
    read(from_server, buffer, sizeof(buffer));
    close(from_server);
    //close(to_server);
    up= open(buffer, O_WRONLY);
    sprintf(buffer, "%d", getpid());
    mkfifo(buffer,0600);
    write (up, buffer, sizeof(buffer));
    down=open(buffer,O_RDONLY,0);
    remove(buffer);
    read (down, buffer, sizeof(buffer));
    printf("[client 1] [%s]\n", buffer);
    

  } else
    {//first client
    sprintf(buffer, "%d", getpid());
    mkfifo(buffer, 0600);
    down=open(buffer, O_RDONLY, 0);
    remove(buffer);
    read(down,buffer,256);
    up=open(buffer,O_WRONLY,0);
    write (up, "conf", sizeof("conf"));

    

  }

  while (1) {

    if (which_client) {//second client

      printf("input: ");
      fgets(buffer, sizeof(buffer),stdin);
      write(up,buffer,sizeof(buffer));

    } else {

      read(down,buffer,sizeof(buffer));
      printf("received input: [%s]\n",buffer);

    }
    which_client=1-which_client;

  }

  /*
  while (1) {

    char s[256];
    printf("Input a string (all letters, all lowercase): ");
    fgets(s,256,stdin);
    s[strlen(s)-1]=0;
    //printf("input read in to s: [%s]\n",s);
    write(to_server,s,256);
    //printf("wrote text\n");
    read(from_server,s,256);
    printf("Received modified string: [%s]\n",s);


    }*/
}

/*
  int to_server, from_server, from_client, to_client;
  char buffer[256];


  int which_client=establish_connection_client(&to_server, &from_server);

  if (which_client) { //yes is the second client, no is the first
    
    read(from_server, buffer, sizeof(buffer));
    close(from_server);
    //close(to_server);
    to_client = open(buffer, O_WRONLY);
    sprintf(buffer, "%d", getpid());
    mkfifo(buffer,0600);
    write (to_client, buffer, sizeof(buffer));
    from_client=open(buffer,O_RDONLY,0);
    remove(buffer);
    read (from_client, buffer, sizeof(buffer));
    printf("[client 1] %s\n", buffer);
    

  } else {//first client
    sprintf(buffer, "%d", getpid());
    mkfifo(buffer, 0600);
    from_client=open(buffer, O_RDONLY, 0);
    remove(buffer);
    read(from_client,buffer,256);
    int to_client=open(buffer,O_WRONLY,0);
    write (to_client, "conf", sizeof("conf"));

    

  }

  while (1) {


  }*/


