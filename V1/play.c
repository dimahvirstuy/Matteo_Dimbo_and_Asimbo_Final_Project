#include "heads.h"
//spy is 1, scout is 2, bomb-killer is 3, 4-10 are 4-10, flag is 0, bomb is 11, empty is -1, blocked is -2
int pieces[10][10] = {{11, 11, 11, 11, 11, 11, 10, 9, 8, 8}, {7, 7, 7, 6, 6, 6, 6, 5, 5, 5}, {5, 4, 4, 4, 4, 3, 3, 3, 3, 3}, {2, 2, 2, 2, 2, 2, 2, 2, 1, 0}, {-1. -1. -2. -2. -1. -1. -2. -2. -1. -1}, {-1. -1. -2. -2. -1. -1. -2. -2. -1. -1}, {11, 11, 11, 11, 11, 11, 10, 9, 8, 8}, {7, 7, 7, 6, 6, 6, 6, 5, 5, 5}, {5, 4, 4, 4, 4, 3, 3, 3, 3, 3}, {2, 2, 2, 2, 2, 2, 2, 2, 1, 0}};
//1 is white, 0 is black, -1 is no loyalty, -2 is blocked
int loyalty[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {-1, -1, -2, -2, -1, -1, -2, -2, -1, -1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


int setup() {
  printf ("white will now setup their side\n");
  white_setup();
  printf ("black will now setup their side\n");
  black_setup();
  printf ("setup complete! here is the board\n");
  display_board();
  return 1;
}
int white_setup() {
  int input;
  while(1) {
    display_board_white();
    printf("input the x coordinate and y coordinate of the piece you would like to move, followed by the x and y coordinates of the destination, or 0 if you do not wish to make and further changes, or 1 if you would like an example\n");
    fgets(input, sizeof(input), stdin);
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
}
int black_setup() {
    int input;
  while(1) {
    display_board_black();
    printf("input the x coordinate and y coordinate of the piece you would like to move, followed by the x and y coordinates of the destination, or 0 if you do not wish to make and further changes, or 1 if you would like an example\n");
    fgets(input, sizeof(input), stdin);
    if (input == 1) {
      printf("to move the piece at (3, 0) to (2, 1), you would input 3021\n");
    }
    else if (input == 0) {
      printf("setup complete\n");
      return 1;
    }
    else if (input <= 1000) {
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
}
int display_board() {
  int i;
  int j;
  printf("NUETRAL BOARD:\n\n");
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
      else {
	printf("%d | ", loyalty[i][j]);
      }
    }
  }
  printf("\n");
  return 1;
}
int display_board_white() {
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
	if (pieces[i][j] == 0) {
	  printf("F | ");
	}
	else if (pieces[i][j] == 11) {
	  printf("B | ");
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
	if (pieces[i][j] == 0) {
	  printf("F | ");
	}
	else if (pieces[i][j] == 11) {
	  printf("B | ");
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
}
int main() {
  display_board_white();
  display_board_black();
  display_board();
  
  //setup();
}
