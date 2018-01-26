#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define WKP "55023"
#define HANDSHAKE_BUFFER_SIZE 100
#define ACK "confirmation"

int is_proper_input(char ** args);
int do_move(int pieces[10][10],int loyalty[10][10],int,int coord[4],int);
int num_tokens(char *, char *);
char ** parse_args(char *, char *);
int array_of_str_len(char **);
int is_valid_swap(int args[4], int side, int loyal[10][10]);
int swap(int board[10][10], int moves[4]);
int setup(int pieces[10][10],int loyal[10][10],int side);
int display_board(int board[10][10],int loyal[10][10],int side);
int display_loyalty(int loyal[10][10]);
int server_handshake(int *, int num);
int client_handshake(int *);
char * board_setup_to_str(int pieces[10][10]);
int setup_two(int pieces[10][10], int loyal[10][10], int);
int reverse_board(int, int pieces[10][10], int loyal[10][10]);
void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server);


