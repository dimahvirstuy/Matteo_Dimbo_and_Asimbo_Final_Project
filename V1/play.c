#include "heads.h"

//spy is 10, scout is 9, bomb-killer is 8, 1-7 are 1-7, flag is -1, bomb is 11, empty is 0, blocked is -2
//int pieces[10][10] = {{11, 11, 11, 11, 11, 11, 1, 2, 3, 3}, {4, 4, 4, 5, 5, 5, 5, 6, 6, 6}, {6, 7, 7, 7, 7, 8, 8, 8, 8, 8}, {9, 9, 9, 9, 9, 9, 9, 9, 10, -1}, {0, 0, -2, -2, 0, 0, -2, -2, 0, 0}, {0, 0, -2, -2, 0, 0, -2, -2, 0, 0}, {11, 11, 11, 11, 11, 11, 1, 2, 3, 3}, {4, 4, 4, 5, 5, 5, 5, 6, 6, 6}, {6, 7, 7, 7, 7, 8, 8, 8, 8, 8}, {9, 9, 9, 9, 9, 9, 9, 9, 10, -1}};
//1 is white, 0 is black, -1 is no loyalty, -2 is blocked
//int loyalty[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};





//returns number of tokens separated by delim in string s
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

int setup(int pieces[10][10],int loyal[10][10], int side) {
  char input_string[100];
  int input;
  while(1) {
    display_board(pieces,loyal,side);
    printf("input the x coordinate and y coordinate of the piece you would like to move, followed by the x and y coordinates of the destination, with each coordinate separated by spaces. Or input 0 if you do not wish to make and further changes, or 1 if you would like an example\n");
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
      }
    }
    else if (array_of_str_len(args)==4){

      //char ** args=parse_args(input_string," ");
      int coordinates[4];
      sscanf(args[0],"%d",coordinates);
      sscanf(args[1],"%d",coordinates+1);
      sscanf(args[2],"%d",coordinates+2);
      sscanf(args[3],"%d",coordinates+3);
      printf("args[0]: %d\n",coordinates[0]);
      printf("args[1]: %d\n",coordinates[1]);
      printf("args[2]: %d\n",coordinates[2]);
      printf("args[3]: %d\n",coordinates[3]);
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
/*int black_setup() {
  char input_string[5];
  int input;
  while(1) {
  display_board_black();
  printf("input the x coordinate and y coordinate of the piece you would like to move, followed by the x and y coordinates of the destination, with each coordinate separated by spaces. Or input 0 if you do not wish to make and further changes, or 1 if you would like an example\n");
  fgets(input_string, sizeof(input_string), stdin);
  input_string[strlen(input_string)-1]=0;
  sscanf(input_string,"%d",&input);
  if (input == 1) {
  printf("to move the piece at (3, 0) to (2, 1), you would input 3021\n");
  }
  else if (input == 0) {
  printf("setup complete\n");
  return 1;
  }
  else {

  char ** args=parse_args(input_string," ");
  if (array_of_str_len(args)==4) {
  int coordinates[4];
  sscanf(args[0],"%d",coordinates);
  sscanf(args[1],"%d",coordinates+1);
  sscanf(args[2],"%d",coordinates+2);
  sscanf(args[3],"%d",coordinates+3);
  if (is_valid(coordinates)) {


  }
  else {
  free(args);
  printf("invalid input, try again\n");
  }
  }
  else {
  free(args);
  printf("invald input, try again\n");
  }
  if (input % 10 >= 6 && (input / 100) % 10 >= 6) {
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

/*int display_board_white() {
  int i;
  int j;
  printf("WHITE BOARD:\n\n");
  for (i = 9; i != -1; i--) {
  printf("\n");
  for (j = 0; j < 10; j++) {
  if (j == 0) {
  printf("| ");
  }
  if (loyalty[i][j] == -2) {
  printf("X | ");
  }
  else if (loyalty[i][j] == -1) {
  printf("_ | ");
  }
  else if (loyalty[i][j] == 1) {
  if (pieces[i][j] == -1) {
  printf("F | ");
  }
  else if (pieces[i][j] == 11) {
  printf("B | ");
  }
  else if (pieces[i][j] == 10) {
  printf("S | ");
  }
  else {
  printf("%d | ", pieces[i][j]);
  }
  }
  else if (loyalty[i][j] == 0) {
  printf("O | ");
  }
  }
  }
  printf("\n");
  return 1;
  }
  int display_board_black() {
  int i;
  int j;
  printf("BLACK BOARD:\n\n");
  for (i = 9; i != -1; i--) {
  printf("\n");
  for (j = 0; j < 10; j++) {
  if (j == 0) {
  printf("| ");
  }
  if (loyalty[i][j] == -2) {
  printf("X | ");
  }
  else if (loyalty[i][j] == -1) {
  printf("_ | ");
  }
  else if (loyalty[i][j] == 0) {
  if (pieces[i][j] == -1) {
  printf("F | ");
  }
  else if (pieces[i][j] == 11) {
  printf("B | ");
  }
  else if (pieces[i][j]==10) {
  printf("S | ");
  }
  else {
  printf("%d | ", pieces[i][j]);
  }
  }
  else if (loyalty[i][j] == 1) {
  printf("O | ");
  }
  }
  }
  printf("\n");
  return 1;
  }*/


//int **s are self-explanatory; side = which side is calling (0 is black, 1 is white)
int display_board(int board[10][10], int loyal[10][10], int side) {
  int i;
  int j;
  printf("SIDE %d BOARD:\n\n",side);
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
      else if (loyal[i][j] == side) {
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
      else if (loyal[i][j] == -1*(side-1)) {//for black, -1*(0-1)==1, for white, -1*(1-1)==0
	printf("O | ");
      }
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




/*int setup() {
  printf ("white will now setup their side\n");
  white_setup();
  printf ("black will now setup their side\n");
  black_setup();
  printf ("setup complete! here is the board\n");
  display_loyalty();
  return 1;
  }*/


int main() {

  //spy is 10, scout is 9, bomb-killer is 8, 1-7 are 1-7, flag is -1, bomb is 11, empty is 0, blocked is -2
  int game[10][10] = {{11, 11, 11, 11, 11, 11, 1, 2, 3, 3}, {4, 4, 4, 5, 5, 5, 5, 6, 6, 6}, {6, 7, 7, 7, 7, 8, 8, 8, 8, 8}, {9, 9, 9, 9, 9, 9, 9, 9, 10, -1}, {0, 0, -2, -2, 0, 0, -2, -2, 0, 0}, {0, 0, -2, -2, 0, 0, -2, -2, 0, 0}, {11, 11, 11, 11, 11, 11, 1, 2, 3, 3}, {4, 4, 4, 5, 5, 5, 5, 6, 6, 6}, {6, 7, 7, 7, 7, 8, 8, 8, 8, 8}, {9, 9, 9, 9, 9, 9, 9, 9, 10, -1}};
  //1 is white, 0 is black, -1 is no loyalty, -2 is blocked
  int sides[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


  //int board[10][10];


  display_board(game,sides,0);
 

  display_board(game,sides,1);
 
  display_loyalty(sides);

  setup(game,sides,0);
  //setup();
  
  //setup();
}
