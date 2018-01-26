#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#ifndef NETWORKING_H
#define NETWORKING_H

#define BUFFER_SIZE 256
#define PORT "9001"
#define PORT_2 "9002"
#define TEST_IP "127.0.0.1"

void error_check(int i, char *s);
int server_setup();
int server_setup_2();
int server_connect(int sd);
int client_setup(char * server);
int server_connect_init(int sd,int send);
int client_setup_init(char * server, int * sd);


#endif
