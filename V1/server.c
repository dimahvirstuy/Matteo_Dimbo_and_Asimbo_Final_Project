#include "heads.h"

//this program will facilitate connection between clients by pairing them together so they can begin the game
//Curent Working Version: handles clients, waits for two connections and pairs them with eachother, then loops to handle more clients

int Setup_WKP () {
  int fd;
  mkfifo(WKP, 0666);
  fd = open(WKP, O_RDONLY);
  return fd;
  
}

char * Establish_Connection_1 () {
  int fd; //recieving first signal
  fd = Setup_WKP();
  char private_pipe[100];
  read(fd, private_pipe, sizeof(private_pipe));
  int fd2; //confirming connection
  fd2 = open(private_pipe, O_WRONLY);
  char conf[100] = "Connection Confirmation";
  write(*fd2, conf, sizeof(conf));
  char priv_conf[100];
  read(fd2, priv_conf, sizeof(priv_conf));
  char request[100] = "succesfully established connection, waiting for second client...";
  write(fd2, request, sizeof(request));
  close(fd);
  return private_pipe;
  
}
int Establish_Connection_2 () {
  int fd; //recieving first signal
  fd = Setup_WKP();
  char private_pipe[100];
  read(fd, private_pipe, sizeof(private_pipe));
  //int fd2; //confirming connection
  fd2 = open(private_pipe, O_WRONLY);
  char conf[100] = "Connection Confirmation";
  write(fd2, conf, sizeof(conf));
  char priv_conf[100];
  read(fd, priv_conf, sizeof(priv_conf));
  char request[100] = "succesfully established connection, await connection from first client...";
  write(fd2, request, sizeof(request));
  close(fd);
  return fd2;
}




int main () {

  int connection_pid;
  
  while(1) {
    int to_client;
    char * client_1;
    char * client_2;
    client_1 = Establish_Connection_1();
    client_2 = Establish_Connection_2();
    write(client_1, client_2, sizeof(client_2));
    write(client_2, client_1, sizeof(client_1));
    close(client_1);
    close(client_2);
  }
}
