#include "networking.h"
#include "heads.h"

static void sighandler(int signo) {
  if (signo==SIGINT) {
    printf("type 'exit' to exit\n");
  }
}


int is_ip(char * s) {

  char ** a=parse_args(s,".");
  if (4!=array_of_str_len(a)) {
    free(a);
    return 0;
  }
  int i=0;
  while (i<4) {
    int check=0;
    sscanf(a[i],"%d",&check);
    if (check<0 || check>255) {
      free(a);
      return 0;
    }
    i++;
  }
  return 1;

}

int main(int argc, char **argv) {

  
  int server_socket, which_client,listen_socket,use_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    which_client = client_setup_init( argv[1],&server_socket);
  else
    which_client = client_setup_init( TEST_IP,&server_socket );


  //use select so you can exit
  if (which_client) {//second client
    read(server_socket,buffer,sizeof(buffer));
    printf("received ip: [%s]\n",buffer);
    close(server_socket);
    listen_socket=server_setup_2();
    use_socket=server_connect(listen_socket);



  } else {//first client
    printf("waiting for another client\n");
    read(server_socket,buffer,sizeof(buffer));//for some reason this is needed
    read(server_socket,buffer,sizeof(buffer));
    while (1) {
      printf("input IP address:\n");
      //check if proper IP
      fgets(buffer,sizeof(buffer),stdin);
      buffer[strlen(buffer)-1]=0;
      char temp[256];
      strcpy(temp,buffer);
      if (is_ip(temp))
	break;
      else
	printf("improper IP\n");
    }
    write(server_socket,buffer,sizeof(buffer));
    close(server_socket);
    use_socket=client_setup(buffer);




  }

  signal(SIGINT,sighandler);

  int turn=0;

  //spy is 10, scout is 9, bomb-killer is 8, 1-7 are 1-7, flag is -1, bomb is 11, empty is 0, blocked is -2
  
  int pieces[10][10] = { {11,-1,11,9,6,8,5,3,1,8}, {5,11,2,9,8,6,8,5,10,11}, {11,3,9,4,9,7,8,11,7,4}, {9,6,9,9,5,6,7,6,9,7}, {0,0,-2,-2,0,0-2,-2,0,0}, {0,0,-2,-2,0,0-2,-2,0,0}, {9,5,9,7,5,9,9,5,6,9}, {6,4,7,6,8,7,11,4,9,6}, {3,11,2,11,9,8,3,11,10,8}, {11,-1,11,5,8,4,9,1,8,7} };

  //1 is white, 0 is black, -1 is no loyalty, -2 is blocked
  //0 is black, 1 is revealed black, 2 is white, 3 is revealed white
  int loyalty[10][10] = {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  reverse_board(which_client,pieces,loyalty);

  if (setup(pieces, loyalty, which_client)==-37) {
    printf("exiting\n");
    write(use_socket,"exit",10);
    close(use_socket);

    exit(0);
  }
  char * set_board=board_setup_to_str(pieces);
  //printf("set_board: [%s]\n",set_board);
  write(use_socket,set_board,HANDSHAKE_BUFFER_SIZE);
  free(set_board);
  
  read(use_socket,buffer,HANDSHAKE_BUFFER_SIZE);
  //printf("buffer: [%s]\n",buffer);
  if (!strcmp(buffer,"exit")) {
    printf("opponent exited\nType anything to exit:\n");
    fgets(buffer,sizeof(buffer),stdin);
    close(use_socket);

    exit(0);
  }
  //printf("buffer: [%s]\n",buffer);
  //printf("buffer len: %d\n",strlen(buffer));
  //if (strlen(buffer)!=88)
  //continue;
  //printf("buffer: [%s]\n",buffer);
  //display_board(pieces,loyalty,2-which_client);
  char ** new_stuff=parse_args(buffer," ");
  //printf("pasred\n");
  int i=0;
  int r=3;
  int c=9;
  for (;r>=0;r--) {
    while (c>=0) {
      //printf("%d\n",i);
      sscanf(new_stuff[i],"%d",&(pieces[r][c]));
	
      i++;
      c--;
	       
    }
    c=9;
    //reading from other client

  }
  free(new_stuff);
  //display_board(pieces,loyalty,2-which_client);

  fd_set read_fds;
  //game play!!!!!!!!!!!!!
  while (1) {
    if (which_client==turn) {
      //printf("[client %d] down: %d | up : %d\n",which_client,down,up);
      //fseek(stdin,0,SEEK_END);
      display_board(pieces,loyalty,which_client);
      printf("input move:\n");

      //select?
      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);//add stdin
      FD_SET(use_socket, &read_fds);//add pipe

      //printf("before select\n");
      select(use_socket+1,&read_fds,NULL,NULL,NULL);
      //printf("post select\n");

      if (FD_ISSET(use_socket, &read_fds)) {//if reading from other client
	read(use_socket,buffer,sizeof(buffer));
	if (!strcmp(buffer,"exit")) {
	  printf("opponent exited.\nType anything to exit:\n");

	  fgets(buffer,sizeof(buffer),stdin);
	  close(use_socket);

	  exit(0);
	}
      }
      else if (FD_ISSET(STDIN_FILENO,&read_fds)) {
	fgets(buffer,sizeof(buffer),stdin);
	buffer[strlen(buffer)-1]=0;
	char send[sizeof(buffer)];
	strcpy(send,buffer);
      
	if (!strcmp(buffer,"exit")) {
	  printf("exiting\n");
	  write(use_socket,buffer,sizeof(buffer));
	  close(use_socket);

	  exit(0);
	}
	//write(up,buffer,sizeof(buffer));
	char ** args=parse_args(buffer," ");

      
	if (!is_proper_input(args)) {
	  free(args);
	  printf("improper input\n");
	  continue;
	}
	
	int coordinates[4];
	/*sscanf(args[0],"%d",coordinates);
	  sscanf(args[1],"%d",coordinates+1);
	  sscanf(args[2],"%d",coordinates+2);
	  sscanf(args[3],"%d",coordinates+3);*/

	int i=0;

	sscanf(args[0],"%d",coordinates);

      
	sscanf(args[1],"%d",coordinates+1);

      
	sscanf(args[2],"%d",coordinates+2);
      
      
	sscanf(args[3],"%d",coordinates+3);
      
      
	//free(args);
	int res=do_move(pieces,loyalty,which_client,coordinates,1);
	//printf("move res: %d\n",res);
	if (res==-1)
	  continue;
	else if (res==100) {
	  printf("VICTORY\n");
	  write(use_socket,send,sizeof(send));
	  free(args);
	  break;
	}
	

	write(use_socket,send,sizeof(send));
	//printf("client %d wrote successfully\n",which_client);
	free(args);
	//write(up,args[1],sizeof(args[1]));
	//write(up,args[2],sizeof(args[2]));
	//write(up,args[3],sizeof(args[3]));
      
	display_board(pieces,loyalty,which_client);
	//display_loyalty(loyalty);
	//generic_print(pieces);
      }
    }

    else {
 
      display_board(pieces,loyalty,which_client);
      printf("awaiting opponent's move\n");
 
      int coordinates[4];

      //insert select statement
      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);//add stdin
      FD_SET(use_socket, &read_fds);//add pipe

      //printf("before select\n");
      select(use_socket+1,&read_fds,NULL,NULL,NULL);
      //printf("post select\n");

      if (FD_ISSET(STDIN_FILENO, &read_fds)) {//if reading from stdin

	
	fgets(buffer,sizeof(buffer),stdin);
	buffer[strlen(buffer)-1]=0;
	if (!strcmp(buffer,"exit")) {
	  printf("Exiting\n");
	  write(use_socket,buffer,sizeof(buffer));
	  close(use_socket);

	  exit(0);
	}
	continue;

      }
      else if (FD_ISSET(use_socket, &read_fds)) {


	read(use_socket,buffer,sizeof(buffer));
	if (!strcmp(buffer,"exit")) {
	  printf("opponent exited.\nType anything to exit:\n");

	  fgets(buffer,sizeof(buffer),stdin);
	  close(use_socket);

	  exit(0);
	}

	char ** args = parse_args(buffer," ");
	sscanf(args[0],"%d",coordinates);
	sscanf(args[1],"%d",coordinates+1);
	sscanf(args[2],"%d",coordinates+2);
	sscanf(args[3],"%d",coordinates+3);
	free(args);

	int i=0;
	for (;i<4;i++)
	  coordinates[i]=9-coordinates[i];

	//printf("doing opponent's move\n");
	int res=do_move(pieces,loyalty,2-which_client,coordinates,0);
   
	/*else*/ if (res==100) {
	  printf("YOU LOSE\n");
	  break;
	}
	display_board(pieces,loyalty,which_client);
  
      }
    }
    turn = 2-turn;
  }
}
/*
  while (1) {
    if (which_client==turn) {
      printf("enter data:\n");
      fgets(buffer,sizeof(buffer),stdin);
      buffer[strlen(buffer)-1]=0;
      write(use_socket,buffer,sizeof(buffer));

    }
    else {
      printf("receiving data:\n");
      read(use_socket,buffer,sizeof(buffer));
      printf("data: [%s]\n",buffer);



    }
    turn=2-turn;
    }*/
  /*
  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
    }*/

