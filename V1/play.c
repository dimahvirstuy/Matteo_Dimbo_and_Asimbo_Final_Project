#include "heads.h"

//spy is 10, scout is 9, bomb-killer is 8, 1-7 are 1-7, flag is -1, bomb is 11, empty is 0, blocked is -2
//int pieces[10][10] = {{11, 11, 11, 11, 11, 11, 1, 2, 3, 3}, {4, 4, 4, 5, 5, 5, 5, 6, 6, 6}, {6, 7, 7, 7, 7, 8, 8, 8, 8, 8}, {9, 9, 9, 9, 9, 9, 9, 9, 10, -1}, {0, 0, -2, -2, 0, 0, -2, -2, 0, 0}, {0, 0, -2, -2, 0, 0, -2, -2, 0, 0}, {11, 11, 11, 11, 11, 11, 1, 2, 3, 3}, {4, 4, 4, 5, 5, 5, 5, 6, 6, 6}, {6, 7, 7, 7, 7, 8, 8, 8, 8, 8}, {9, 9, 9, 9, 9, 9, 9, 9, 10, -1}};
//1 is white, 0 is black, -1 is no loyalty, -2 is blocked
//int loyalty[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


//returns number of tokens separated by delim in string s

int is_proper_input(char ** args) {
  int i=0;
  return (array_of_str_len(args)==4) &&
    (sscanf(args[0],"%d",&i)) &&
    (sscanf(args[1],"%d",&i)) &&
    (sscanf(args[2],"%d",&i)) &&
    (sscanf(args[3],"%d",&i));
}

int num_tokens(char * s, char * delim){
  //printf("s is %s\n",s);
  int ret=1;
  int i=0;
  for(;i<strlen(s);i++) {
    if(s[i]==delim[0]) {
      ret++;
      //printf("added %d\n",i);
    }
  }
  //if (!strcmp(s,"exit"))
  //printf("exit command num tokens\n");
  return ret;
}

char** parse_args(char * line, char * delim) {
  char ** s=(char **)calloc(sizeof(char *),num_tokens(line, delim)+1);
  //printf("line: %s\n",line);
  int i=0;
  while (line){
    //if (i==0 && *line!=*delim)
    s[i]=line;
    //printf("line before strsep: %s\n",line);
    strsep(&line, delim);
    //printf("line after strsep: %s\n",line);
    i++;
  }
  return s;
}

int array_of_str_len(char ** s) {
  int i=0;
  while (s[i++]);
  return --i;//subtract one because while loop adds one extra
}

/*int white_setup() {
  char input_string[5];
  int input;
  while(1) {
  display_board_white();
  printf("input the x coordinate and y coordinate of the piece you would like to move, followed by the x and y coordinates of the destination, or 0 if you do not wish to make and further changes, or 1 if you would like an example\n");
  fgets(input_string, sizeof(input), stdin);
  input_string[strlen(input_string)-1]=0;
  sscanf(input_string,"%d",&input);
  if (input == 1) {
  printf("to move the piece at (3, 0) to (2, 1), you would input 3021\n");
  }
  else if (input == 0) {
  printf("setup complete\n");
  return 1;
  }
  else if (input <= 1000) {
  if (input % 10 <= 3 && (input / 100) % 10 <= 3) {
  int holder = pieces[(input / 100) % 10][input / 1000];
  pieces[(input / 100) % 10][input / 1000] = pieces[input % 10][(input/10) % 10];
  pieces[input % 10][(input/10) % 10] = holder;
  }
  }
  else {
  printf("invalid input, try again\n");
  }
  }
  return 1;
  }*/

int is_valid_swap(int args[4],int side,int loyal[10][10]) {
  int i=((args[0]>-1 && args[0]<10) &&
	 (args[1]>-1 && args[1]<10) &&
	 (args[2]>-1 && args[2]<10) &&
	 (args[3]>-1 && args[3]<10));
  int j=( loyal[args[0]][args[1]]==side && loyal[args[2]][args[3]]==side);
  return i && j;

}

int swap(int board[10][10], int moves[4]) {
  int temp=board[moves[0]][moves[1]];
  board[moves[0]][moves[1]]=board[moves[2]][moves[3]];
  board[moves[2]][moves[3]]=temp;
  return 1;
}

int setup_two(int pieces[10][10], int loyal[10][10],int side) {
  char input_string[100];
  int input;

  fgets(input_string, 100, stdin);
  input_string[strlen(input_string)-1]=0;
  char ** args=parse_args(input_string," ");
  if (array_of_str_len(args)==1) {
    int check=sscanf(args[0],"%d",&input);
    if (!check) {
      printf("not an integer, try again\n");
    }
    //free(args);
    else if (input == 1) {
      printf("to move the piece at (3, 0) to (2, 1), you would input 3021\n");
    }
    else if (input == 0) {
      printf("setup complete\n");
      free(args);
      return 1;
    }
    else {
      printf("invalid single integer, try again\n");
      return 0;
    }
  }
  else if (array_of_str_len(args)==4){
    //char ** args=parse_args(input_string," ");
    int coordinates[4];
    sscanf(args[0],"%d",coordinates);
    sscanf(args[1],"%d",coordinates+1);
    sscanf(args[2],"%d",coordinates+2);
    sscanf(args[3],"%d",coordinates+3);
    /*printf("args[0]: %d\n",coordinates[0]);
      printf("args[1]: %d\n",coordinates[1]);
      printf("args[2]: %d\n",coordinates[2]);
      printf("args[3]: %d\n",coordinates[3]);*/
    if (is_valid_swap(coordinates,side,loyal)) {
      swap(pieces,coordinates);
      //free(args);
    }
    else {
      //free(args);
      printf("invalid swap, try again\n");
      return 0;
    }
  }
  else {
    //free(args);
    printf("invald input, try again\n");
    return 0;
  }
  free(args);
  return 0;
}

int setup(int pieces[10][10],int loyal[10][10], int side) {
  char input_string[100];
  int input;
  while(1) {
    display_board(pieces,loyal,side);
    printf("input the x coordinate and y coordinate of the piece you would like to move, followed by the x and y coordinates of the destination, with each coordinate separated by spaces. Or input 0 if you do not wish to make and further changes, or 1 if you would like an example\n");
    fgets(input_string, 100, stdin);
    input_string[strlen(input_string)-1]=0;
    if(!strcmp(input_string,"exit")) {
      return -37;
    }
    char ** args=parse_args(input_string," ");
    if (array_of_str_len(args)==1) {
      int check=sscanf(args[0],"%d",&input);
      if (!check) {
	printf("not an integer, try again\n");
      }
      //free(args);
      else if (input == 1) {
	printf("to move the piece at (3, 0) to (2, 1), you would input 3021\n");
      }
      else if (input == 0) {
	printf("setup complete\n");
	free(args);
	return 1;
      }
      else {
	printf("invalid single integer, try again\n");
      }
    }
    else if (array_of_str_len(args)==4){
      //char ** args=parse_args(input_string," ");
      int coordinates[4];
      sscanf(args[0],"%d",coordinates);
      sscanf(args[1],"%d",coordinates+1);
      sscanf(args[2],"%d",coordinates+2);
      sscanf(args[3],"%d",coordinates+3);
      /*printf("args[0]: %d\n",coordinates[0]);
	printf("args[1]: %d\n",coordinates[1]);
	printf("args[2]: %d\n",coordinates[2]);
	printf("args[3]: %d\n",coordinates[3]);*/
      if (is_valid_swap(coordinates,side,loyal)) {
	swap(pieces,coordinates);
	//free(args);

      }
      else {
	//free(args);
	printf("invalid swap, try again\n");
      }
    }
    else {
      //free(args);
      printf("invald input, try again\n");
    }
    free(args);
  }      
  return 1;
}

//int **s are self-explanatory; side = which side is calling (0 is black, 2 is white)
int display_board(int board[10][10], int loyal[10][10], int side) {
  int i;
  int j;
  int loy;
  if (side%2==1) side--;
  printf("SIDE %d BOARD:\n\n",side);
  printf("-|-0-|-1-|-2-|-3-|-4-|-5-|-6-|-7-|-8-|-9-|");
  for (i = 0; i <10; i++) {
    printf("\n");
    for (j = 0; j < 10; j++) {
      loy=loyal[i][j];
      if (loy>-1 && loy%2==1) loy--;
      if (j == 0) {
	printf("%d| ",i);
      }
      if (loyal[i][j] == -2) {
	printf("X | ");
      }
      else if (loyal[i][j] == -1) {
	printf("_ | ");
      }
      else if (loy == side || (loy-1==side)) {
	if (board[i][j] == -1) {
	  printf("F | ");
	}
	else if (board[i][j] == 11) {
	  printf("B | ");
	}
	else if (board[i][j]==10) {
	  printf("S | ");
	}
	else {
	  printf("%d | ", board[i][j]);
	}
      }
      else if (loyal[i][j] == 2-side) {//opponent, not revealed
	printf("0 | ");
      }
      else if (loyal[i][j]==3-side) {
	printf("%d~| ",board[i][j]);
      }
      /*else if (loyal[i][j]==3-side ) {//opponent, revealed
	printf("%d | ",board[i][j]
	}*/
    }
  }
  printf("\n\n");
  return 1;
}

int display_loyalty(int loyal[10][10]) {
  int i;
  int j;
  printf("NUETRAL BOARD:\n\n");
  for (i = 0; i <10; i++) {
    printf("\n");
    for (j = 0; j < 10; j++) {
      if (j == 0) {
	printf("| ");
      }
      if (loyal[i][j] == -2) {
	printf("X | ");
      }
      else if (loyal[i][j] == -1) {
	printf("_ | ");
      }
      else {
	printf("%d | ", loyal[i][j]);
      }
    }
  }
  printf("\n");
  return 1;
}

//reverses board so that depending on what the "side" of the process is it can still have its own pieces closest to it
int reverse_board(int side, int game[10][10], int loyal[10][10]) {
  if (side==2) {
    int r=0;
    int c=0;
    for (;r<10;r++) {
      for (;c<5;c++) {
	int moves[]={r,c,9-r,9-c};
	swap(game,moves);
	swap(loyal,moves);
      }
      c=0;
    }
    return 1;
  }
  return 0;
}

int xor(int a, int b) {
  return (a || b) && !(a && b);
}

int distance(int a, int b) {
  if (a>b)
    return a-b;
  else
    return b-a;
}

int min(int a, int b) {
  if (a>b)
    return b;
  else
    return a;
}

int max(int a, int b) {
  if (a>b)
    return a;
  else
    return b;
}

int is_valid_move_scout(int loyal[10][10],int player_loyalty, int moves[4]) {
  printf("scout check\n");
  if (abs(moves[3]-moves[1])>1) {
    int i=min(moves[1],moves[3])+1;
    if (moves[2]!=moves[0])
      return 0;
    while (distance(i,max(moves[1],moves[3]))>0) {
      int check=loyal[moves[0]][i];
      if (check>0 && check%2==1) check--;
      if (check==player_loyalty || check==-2 || check==2-player_loyalty)
	return 0;
      i++;
    }
  } else if (abs(moves[2]-moves[0])>1){
    int i=min(moves[0],moves[2])+1;
    if (moves[3]!=moves[1])
      return 0;
    while (distance(i,max(moves[0],moves[2]))>0) {
      //printf("scout check i: %d\n",i);
      int check=loyal[i][moves[1]];
      if (check>0 && check%2==1) check--;
      if (check==player_loyalty || check==-2 || check==2-player_loyalty) {
	printf("scout check %d: %d\n",i,check);
	return 0;
      }
      i++;
    }
  }
  return 1;
}

int is_valid_move(int game[10][10], int loyal[10][10], int player_loyalty, int moves[4]) {
  //is piece at square moves(0,1) your loyalty
  //if not B or F (11 or -1)
  //is moves (2,3) adjacent OR is moves(0,1) a 9
  //if it is adjacent, is the square you are moving to valid
  //if it is a 9, are all the squares in between empty

  //printf("loyal[moves[0]][moves[1]]: %d\n",loyal[moves[0]][moves[1]]);
  //printf("loyal[moves[2]][moves[3]]: %d\n",loyal[moves[2]][moves[3]]);
  int curr_loyalty=loyal[moves[0]][moves[1]];
  int target_loyalty=loyal[moves[2]][moves[3]];
  
  if (curr_loyalty>=0 && curr_loyalty%2==1) curr_loyalty--;
  if (target_loyalty>=0 && target_loyalty%2==1) target_loyalty--;
  
  return (((curr_loyalty==player_loyalty) &&
	   (target_loyalty!=-2) && (target_loyalty!=player_loyalty))
	  &&
	  (game[moves[0]][moves[1]]!=11 && game[moves[0]][moves[1]]!=-1)
	  &&
	  ((xor(abs(moves[3]-moves[1])==1,abs(moves[2]-moves[0])==1) && xor(abs(moves[3]-moves[1])==0,abs(moves[2]-moves[0])==0))
	   ||
	   ((game[moves[0]][moves[1]]==9) && is_valid_move_scout(loyal,player_loyalty,moves))));
}

/*int setup() {
  printf ("white will now setup their side\n");
  white_setup();
  printf ("black will now setup their side\n");
  black_setup();
  printf ("setup complete! here is the board\n");
  display_loyalty();
  return 1;
  }*/

int do_move(int game[10][10], int loyal[10][10], int player_loyalty, int moves[4], int is_turn) {
  if (player_loyalty%2==1) player_loyalty--;
  if (is_valid_move(game,loyal,player_loyalty,moves)) {
    printf("valid\n");
    //if advancing to empty square
    if (loyal[moves[2]][moves[3]]==-1) {
      if (is_turn) printf("Your piece advances.\n");
      else printf("Opponent piece advances.\n");
      
      swap(game,moves);
      swap(loyal,moves);
      return game[moves[2]][moves[3]];
      //if attacking opponent
    } else if (loyal[moves[2]][moves[3]]==(2-player_loyalty) || loyal[moves[2]][moves[3]]==(3-player_loyalty)) {
      int player=game[moves[0]][moves[1]];
      int opponent=game[moves[2]][moves[3]];
      //spy(10) and 1/everything else
      //8 and 11(bomb)
      //bomb and everything
      //flag (-1)
      
      if (player==10) {//player is spy
	if (opponent==1) {//spy kills 1
	  if (is_turn) printf("Player: [%d] Opponent: [%d]. You advance, opponent piece defeated.\n",player,opponent);
	  else printf("Opponent: [%d] Player: [%d]. Opponent advances, your piece defeated.\n",player,opponent);
	  game[moves[2]][moves[3]]=player;
	  game[moves[0]][moves[1]]=0;
	  loyal[moves[2]][moves[3]]=player_loyalty;
	  //reveal
	  if (loyal[moves[2]][moves[3]]%2==0) loyal[moves[2]][moves[3]]++;
	  loyal[moves[0]][moves[1]]=-1;
	  return player;

	} else {//everything other than 1 kills spy
	  if (is_turn) printf("Player: [%d] Opponent: [%d]. Your piece is defeated.\n",player,opponent);
	  else printf("Opponent: [%d] Player: [%d]. Your piece wins.\n",player,opponent);
	  game[moves[0]][moves[1]]=0;
	  loyal[moves[0]][moves[1]]=-1;
	  //reveal
	  if (loyal[moves[2]][moves[3]]%2==0) loyal[moves[2]][moves[3]]++;
	  return opponent;
	}
      
      } else if (opponent==11) {//opponent is bomb
	if (player==8) {//8 defuses bomb
	  if (is_turn) printf("Player: [%d] Opponent: [%d]. You advance, opponent piece defeated.\n",player,opponent);
	  else printf("Opponent: [%d] Player: [%d]. Opponent advances, your piece defeated.\n",player,opponent);
	  game[moves[2]][moves[3]]=player;
	  game[moves[0]][moves[1]]=0;
	  loyal[moves[2]][moves[3]]=player_loyalty;
	  //reveal
	  if (loyal[moves[2]][moves[3]]%2==0) loyal[moves[2]][moves[3]]++;
	  loyal[moves[0]][moves[1]]=-1;
	  return player;

	} else {//bomb kills everything else
	  if (is_turn) printf("Player: [%d] Opponent: [%d]. Your piece is defeated.\n",player,opponent);
	  else printf("Opponent: [%d] Player: [%d]. Your piece wins.\n",player,opponent);

	  game[moves[0]][moves[1]]=0;
	  loyal[moves[0]][moves[1]]=-1;
	  //reveal
	  if (loyal[moves[2]][moves[3]]%2==0) loyal[moves[2]][moves[3]]++;
	  return opponent;
	}
      } else if (opponent==-1) {//opponent is flag

	//printf("YOU WIN!\n");
	return 100;
	//victory
      }
      //do battle
      else if (player<opponent) {//you are stronger
	if (is_turn) printf("Normal move, you are stronger. Player: [%d] Opponent: [%d]. You advance, opponent piece defeated.\n",player,opponent);
	else printf("Normal move, you are weaker. Player: [%d] Opponent: [%d]. Your piece is defeated.\n",player,opponent);
	game[moves[2]][moves[3]]=player;
	game[moves[0]][moves[1]]=0;
	loyal[moves[2]][moves[3]]=player_loyalty;
	loyal[moves[0]][moves[1]]=-1;
	//if loyalty of your piece is even (not revealed), reveal by making it odd
	if (loyal[moves[2]][moves[3]]%2==0) loyal[moves[2]][moves[3]]++;
	return player;
      } else if (player>opponent) {//you are weaker
	
	if (is_turn) printf("Normal move, you are weaker. Player: [%d] Opponent: [%d]. Your piece is defeated.\n",player,opponent);
	else printf("Normal move, you are stronger. Player: [%d] Opponent: [%d]. You advance, opponent piece defeated.\n",player,opponent);
	game[moves[0]][moves[1]]=0;
	loyal[moves[0]][moves[1]]=-1;
	//if loyalty of opponent is even, then it has not been revealed; reveal by making it odd
	if (loyal[moves[2]][moves[3]]%2==0) loyal[moves[2]][moves[3]]++;
	return opponent;
      } else if (player==opponent) {//tie
	printf("Normal move, tie. Player: [%d] Opponent: [%d]. Both pieces die.\n",player,opponent);
	game[moves[2]][moves[3]]=0;
	game[moves[0]][moves[1]]=0;
	loyal[moves[2]][moves[3]]=-1;
	loyal[moves[0]][moves[1]]=-1;
	return 0;
      }
    }
  }
  return -1;
}

char * board_setup_to_str(int pieces[10][10]) {
  int r=6;
  int c=0;
  int place=0;
  char * s=(char *)calloc(100,1);

  for (;r<10;r++) {
    while (c<10) {
      sprintf(s+place,"%d",pieces[r][c]);
      if (pieces[r][c]<10 && pieces[r][c]>0)
	place++;
      else
	place+=2;
      sprintf(s+place,"%c",' ');
      place++;
      c++;
    }
    c=0;
  }
  s[strlen(s)]='\n';
  //printf("S: [%s]\n",s);

  return s;
}

/*
int main() {

  //spy is 10, scout is 9, bomb-killer is 8, 1-7 are 1-7, flag is -1, bomb is 11, empty is 0, blocked is -2
  int pieces[10][10] = { {11,-1,11,9,6,8,5,3,1,8}, {5,11,2,9,8,6,8,5,10,11}, {11,3,9,4,9,7,8,11,7,4}, {9,6,9,9,5,6,7,6,9,7}, {0,0,-2,-2,0,0-2,-2,0,0}, {0,0,-2,-2,0,0-2,-2,0,0}, {9,5,9,7,5,9,9,5,6,9}, {6,4,7,6,8,7,11,4,9,6}, {3,11,2,11,9,8,3,11,10,8}, {11,-1,11,5,8,4,9,1,8,7} };

  //1 is white, 0 is black, -1 is no loyalty, -2 is blocked
  //0 is black, 1 is revealed black, 2 is white, 3 is revealed white
  int loyalty[10][10] = {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  //int board[10][10];
  //    {{11, 11, 11, 11, 11, 11, 1, 2, 3, 3}, {4, 4, 4, 5, 5, 5, 5, 6, 6, 6}, {6, 7, 7, 7, 7, 8, 8, 8, 8, 8}, {9, 9, 9, 9, 9, 9, 9, 9, 10, -1}, {0, 0, -2, -2, 0, 0, -2, -2, 0, 0}, {0, 0, -2, -2, 0, 0, -2, -2, 0, 0}, {11, 11, 11, 11, 11, 11, 1, 2, 3, 3}, {4, 4, 4, 5, 5, 5, 5, 6, 6, 6}, {6, 7, 7, 7, 7, 8, 8, 8, 8, 8}, {9, 9, 9, 9, 9, 9, 9, 9, 10, -1}};

  
  //display_board(pieces,loyalty,0);

  //display_board(pieces,loyalty,2);
 
  //display_loyalty(loyalty);

  //reverse_board(2,pieces,loyalty);
  //printf("reversed board\n");
  //display_board(pieces,loyalty,0);
  //display_board(pieces,loyalty,2);
  //display_loyalty(loyalty);
  

  printf("testing do move\n");
  //int moves[]={6,4,5,4};
  //do_move(pieces,loyalty,2,moves);
  //display_board(pieces,loyalty,2);
  //display_loyalty(loyalty);

  char buffer[100];
  while (1) {
    display_board(pieces,loyalty,2);
    printf("input move:\n");
    fgets(buffer,sizeof(buffer),stdin);
    char ** args=parse_args(buffer," ");
    int coordinates[4];
    sscanf(args[0],"%d",coordinates);
    sscanf(args[1],"%d",coordinates+1);
    sscanf(args[2],"%d",coordinates+2);
    sscanf(args[3],"%d",coordinates+3);
    do_move(pieces,loyalty,2,coordinates);
    display_board(pieces,loyalty,2);


  }
  
  printf("\n-----testing is_valid_move()-----\n");
  int moves[]={6,4,4,4};
  if (is_valid_move(pieces,loyalty,1,moves))
    printf("6,4,4,4 is valid\n");
  else
    printf("error\n");
  int moves2[]={3,1,4,1};
  //printf("%d\n",loyalty[3][1]);
  //printf("%d\n",loyalty[4][1]);
    
  if (is_valid_move(pieces,loyalty,0,moves2))
    printf("3,1,4,1 is valid\n");
  else
  printf("error\n");

  //setup(game,sides,0);
  //setup();
  
  //setup();
}*/
