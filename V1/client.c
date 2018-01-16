#include "heads.h"

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
      close(from_server);
      sprintf(buffer, "%d", getpid());
      mkfifo(buffer, 0600);
      down=open(buffer, O_RDONLY, 0);
      remove(buffer);
      read(down,buffer,256);
      up=open(buffer,O_WRONLY,0);
      write (up, "conf", sizeof("conf"));
      printf("wrote conf\n");

    

    }

  int turn=0;
  //spy is 10, scout is 9, bomb-killer is 8, 1-7 are 1-7, flag is -1, bomb is 11, empty is 0, blocked is -2

  
  int pieces[10][10] = { {11,-1,11,9,6,8,5,3,1,8}, {5,11,2,9,8,6,8,5,10,11}, {11,3,9,4,9,7,8,11,7,4}, {9,6,9,9,5,6,7,6,9,7}, {0,0,-2,-2,0,0-2,-2,0,0}, {0,0,-2,-2,0,0-2,-2,0,0}, {9,5,9,7,5,9,9,5,6,9}, {6,4,7,6,8,7,11,4,9,6}, {3,11,2,11,9,8,3,11,10,8}, {11,-1,11,5,8,4,9,1,8,7} };

  //1 is white, 0 is black, -1 is no loyalty, -2 is blocked
  //0 is black, 1 is revealed black, 2 is white, 3 is revealed white
  int loyalty[10][10] = {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  reverse_board(which_client,pieces,loyalty);

  fd_set read_fds;
  
  while (1) {

    display_board(pieces,loyalty,which_client);
    printf("input the x coordinate and y coordinate of the piece you would like to move, followed by the x and y coordinates of the destination, with each coordinate separated by spaces. Or input 0 if you do not wish to make and further changes, or 1 if you would like an example:\n");
    //fflush(stdout);

    

    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);//add stdin
    FD_SET(down, &read_fds);//add pipe

    printf("before select\n");
    select(down+1,&read_fds,NULL,NULL,NULL);
    printf("post select\n");

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {//if reading from stdin
      printf("reading stdin\n");
      int check=setup_two(pieces, loyalty, which_client);
      if (check==1) {
	char * set_board=board_setup_to_str(pieces);
	printf("set_board: [%s]\n",set_board);
	write(up,set_board,HANDSHAKE_BUFFER_SIZE);
	free(set_board);
	break;
      }
      //reading from stdin
    }

    if (FD_ISSET(down,&read_fds)) {//if reading from other client
      printf("reading from other client\n");
      //read(down,buffer,HANDSHAKE_BUFFER_SIZE);
      //printf("buffer: [%s]\n",buffer);
      //read(down,buffer,HANDSHAKE_BUFFER_SIZE);
      //printf("buffer: [%s]\n",buffer);
      read(down,buffer,HANDSHAKE_BUFFER_SIZE);
      printf("buffer: [%s]\n",buffer);

      //printf("buffer len: %d\n",strlen(buffer));
      if (strlen(buffer)!=88)
	continue;
      //printf("buffer: [%s]\n",buffer);
      display_board(pieces,loyalty,2-which_client);
      char ** new_stuff=parse_args(buffer," ");
      printf("pasred\n");
      int i=0;
      int r=3;
      int c=9;
      for (;r>=0;r--) {
	while (c>=0) {
	  printf("%d\n",i);
	  sscanf(new_stuff[i],"%d",&(pieces[r][c]));
	
	  i++;
	  c--;
	       
	}
	c=9;
	//reading from other client

      }
      free(new_stuff);
      display_board(pieces,loyalty,2-which_client);

    }

  }
  close(up);
  close(down);


  
  //working chat
  /*while (1) {
    printf("up: %d | down: %d\n",up,down);
    if (which_client==turn) {

    char * s="[7 9 6 7 6 5 9 9 6 9 4 7 11 8 7 9 4 9 3 11 11 10 5 8 6 8 9 2 11 5 11 1 3 5 8 6 9 11 -1 8 ]";
    printf("strlen: %d s: [%s]\n",strlen(s),s);
    printf("input: ");
    fgets(buffer, sizeof(buffer),stdin);
    printf("wrote: %d\n",write(up,s,91));
    //printf("wrote\n");
    close(down);
    close(up);
    exit(0);

    } else {

    //read(down,buffer,sizeof(buffer));
    //printf("received input: [%s]\n",buffer);
      
    //read(down,buffer,sizeof(buffer));
    //printf("received input: [%s]\n",buffer);
    read(down,buffer,sizeof(buffer));
    printf("received input: [%s]\n",buffer);
    close(down);
    close(up);
    exit(0);

    }
    turn=2-turn;

    }*/


}



