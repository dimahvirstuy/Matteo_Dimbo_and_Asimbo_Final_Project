#include "heads.h"

//this program will facilitate connection between clients by pairing them together so they can begin the game
//Curent Working Version: handles clients, waits for two connections and pairs them with eachother, then loops to handle more clients

char * establish_connection (int num, int * to_client) {
  mkfifo(WKP,0600);
  printf("[server] waiting client %d connection\n",num);
  int from_client=open(WKP,O_RDONLY,0); 
  //char private_pipe[100];

  char * private_pipe=(char *) calloc(1,100);
  //else char private_pipe[100];
  
  read(from_client, private_pipe, sizeof(private_pipe));
  remove(WKP);
  
  //int fd2; //confirming connection
  *to_client = open(private_pipe, O_WRONLY);
  //char conf[100] = "Connection Confirmation";
  printf("[server] writing to client %d\n",num);
  write(*to_client, "connection confirmation", sizeof("connection confirmation"));
  char priv_conf[100];
  read(from_client, priv_conf, sizeof(priv_conf));
  printf("[server] handshake with client %d: [%s]\n",num,priv_conf);
  if (num) {//connection 1
    strcpy(priv_conf,"succesfully established connection, waiting for second client...");
    close(*to_client);
  } else {//connection 0
    strcpy(priv_conf,"succesfully established connection, await connection from first client...");
    free(private_pipe);
  }  
  write(*to_client, priv_conf, sizeof(priv_conf));
  close(from_client);
  return private_pipe;  
}
/*
char * Establish_Connection_2 (int  * fd2) {
  mkfifo(WKP,0600);
  int from_client=open(WKP,O_RDONLY,0); 
  //char private_pipe[100];

  char * private_pipe=(char *) calloc(1,100);
  
  read(from_client, private_pipe, sizeof(private_pipe));
  remove(WKP);
  
  //int fd2; //confirming connection
  *to_client = open(private_pipe, O_WRONLY);
  //char conf[100] = "Connection Confirmation";
  write(*to_client, "connection confirmation", sizeof("connection confirmation"));
  char priv_conf[100];
  read(from_client, priv_conf, sizeof(priv_conf));
  strcpy(priv_conf,"succesfully established connection, await connection from first client...");
 
  write(*to_client, priv_conf, sizeof(priv_conf));
  close(from_client);
  return private_pipe;
  
    int fd; //recieving first signal
    fd = Setup_WKP();
    //char private_pipe[100];
    char * private_pipe=(char *) calloc(1,100);
    read(fd, private_pipe, sizeof(private_pipe));
    //int fd2; //confirming connection
    *fd2 = open(private_pipe, O_WRONLY);
    char conf[100] = "Connection Confirmation";
    write(*fd2, conf, sizeof(conf));
    char priv_conf[100];
    read(fd, priv_conf, sizeof(priv_conf));
    char request[100] = "succesfully established connection, await connection from first client...";
    write(*fd2, request, sizeof(request));
    close(fd);
    return private_pipe;
}
*/
void error_check( int i, char *s ) {
  if ( i < 0 ) {
    printf("[%s] error %d: %s\n", s, errno, strerror(errno) );
    exit(1);
  }
}

/*=========================
  server_setup
  args:

  creates, binds a server side socket
  and sets it to the listening state

  returns the socket descriptor
  =========================*/
int server_setup() {
  int sd, i;

  //create the socket
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  error_check( sd, "server socket" );
  printf("[server] socket created\n");

  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  //IPv4 address
  hints->ai_socktype = SOCK_STREAM;  //TCP socket
  hints->ai_flags = AI_PASSIVE;  //Use all valid addresses
  getaddrinfo(NULL, PORT, hints, &results); //NULL means use local address

  //bind the socket to address and port
  i = bind( sd, results->ai_addr, results->ai_addrlen );
  error_check( i, "server bind" );
  printf("[server] socket bound\n");

  //set socket to listen state
  i = listen(sd, 10);
  error_check( i, "server listen" );
  printf("[server] socket in listen state\n");

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  return sd;
}


int main () {
  //SOCKET CONNECTION!
  int serv_descrip;
  printf("NOTICE: For clients to connect you will need to know the IP of this server\n");
  serv_descrip = server_setup();
  
  
  //int connection_pid;
  /* while(1) {
    int to_client_1;
    int client_0_ip[15];
    char client_0[100];
    //char * client_2;
    client_0_pid=establish_connection(0,&to_client_1);
    //free(client_1);
    establish_connection(1,&to_client_1);
    sprintf(client_0,"%d",client_0_pid);
    //write(to_client_1, client_2, sizeof(client_2));
    write(to_client_1, client_0, sizeof(client_0));
    close(to_client_1);
    //close(to_client_2);

    int to_client_1;
    int client_0_ip;
    char client_0[100]
  }
  /*
}
