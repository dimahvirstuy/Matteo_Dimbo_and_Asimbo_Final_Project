#include "heads.h"

int establish_connection_client(int * fd, int * fd1) {

  char my_pipe[100];
  
  //fd1 = open(my_pipe, O_RDONLY);
  *fd = open(WKP, O_WRONLY);

  sprintf(my_pipe, "%d", getpid());
  mkfifo(my_pipe, 0600);

  
  write(*fd, my_pipe, sizeof(my_pipe));
  *fd1=open(my_pipe,O_RDONLY, 0);
  
  //char conf_rec[100];
  read(*fd1, my_pipe, sizeof(my_pipe));
  remove(my_pipe);
  char conf_send[100] = "confirmation recieved";
  write(*fd, conf_send, sizeof(conf_send));
  char status[100];
  read(*fd, status, sizeof(status));
  close(*fd);
  printf("%s\n", status);
  if (strcmp(status, "succesfully established connection, waiting for second client...") == 0) {
    return 0; //tells the parent function to write in initial client-client connection
  }
  else {
    return 1; //tells the parent function to read in initial client-client connection
  }
  //INCOMPLETE NEEDS TO BE FINISHED AND DEBUGGED
}



int main() {


  int to_server, from_server;
  char buffer[256];


  int which_client=establish_connection_client(&to_server, &from_server);

  if (which_client) {



  } else {




  }







}
