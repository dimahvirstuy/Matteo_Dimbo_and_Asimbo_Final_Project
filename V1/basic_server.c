#include "heads.h"
#include <string.h>
#include <signal.h>

void to_upper(char * s) {

  int i=0;
  while (i<strlen(s))
    s[i++]-=32;

}

static void sighandler(int signo) {
  if (signo==SIGINT) {
    remove(WKP);
    exit(0);
  }
}

int main() {
  signal(SIGINT,sighandler);

  int to_client_1;
  int client_0_pid;
  char client_0[100];

  client_0_pid=server_handshake(&to_client_1,0);
  server_handshake(&to_client_1,1);
  sprintf(client_0,"%d",client_0_pid);
  write(to_client_1, client_0, sizeof(client_0));
  close(to_client_1);
  //int to_client;
  //int from_client;


  //from_client = server_handshake( &to_client,1 );

  /*while (1) {

    char s[256];
    read(from_client,s,256);
    printf("Modifying string\n");
    to_upper(s);
    write(to_client,s,256);



    }*/

}
