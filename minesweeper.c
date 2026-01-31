// AbdulRahman(A)    SadiqAmin(S)    Pawan(P)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Free the allocated memory for the 2D array(A)
void free2DArray(char **arr, int m) {
  int i;
  for (int i = 0; i < m; i++) {
    free(arr[i]);
  }
  free(arr);
}


// Function to read the highest score from the file (P)
float readHighestScore() {
  float highestScore = 0.0;
  FILE *file = fopen("hs.txt", "r");
  if (file != NULL) {
    fscanf(file, "%f", &highestScore);
    fclose(file);
  }
  return highestScore;
}


// Function to write the highest score to the file (P)
void writeHighestScore(float highestScore) {
  FILE *file = fopen("hs.txt", "w");
  if (file != NULL) {
    fprintf(file, "%.2f", highestScore);
    fclose(file);
  }
}


//Calculate score with each move preceeding (P)
int calculateScore(int score, char **revealedgrid, char **hiddengrid, int x, int y) {
  int intGrid;
  if (revealedgrid[y][x] != 'M' && revealedgrid[y][x] != 'E') {
    //since grid elements are char, having another int var to add to score
    switch(hiddengrid[y][x]) {
      case '1':
        intGrid =1;
        break;
      case '2':
        intGrid =2;
        break;
      case '3':
        intGrid=3;
        break;
      case '4':
        intGrid =4;
        break;
      case '5':
        intGrid = 5;
        break;
      case '6':
        intGrid =6;
        break;
      case '7':
        intGrid =7;
        break;
      case '8':
        intGrid =8;
        break;
      }
    score += intGrid;
    }
  return score;
}

// Calculates number of mines based on difficulty level (P)
int calculatemines(int m, int n, int level) {
  int cells = m * n;
  int totalmines;
  float minedensity;
  
  if (level == 1) {
    minedensity = 0.12345679;
  } 
  else if (level == 2) {
    minedensity = 0.15625;
  } 
  else if (level == 3) {
    minedensity = 0.20625;
  }
  totalmines = floor(cells * minedensity);

  // The minimum number of mines in a grid
  if (totalmines < 1) {
    totalmines = 1;
  }
  return totalmines;
}


// Total sum of numbers on cells (P)
int sumcells(char **revealedgrid, int m, int n) {
  int cellsum = 0;
  int i, j, intGrid;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (revealedgrid[i][j] != 'M' && revealedgrid[i][j] !='E') {
        
        switch(revealedgrid[i][j]) {
        case '1':
          intGrid =1;
          break;
        case '2':
          intGrid =2;
          break;
        case '3':
          intGrid=3;
          break;
        case '4':
          intGrid =4;
          break;
        case '5':
          intGrid = 5;
          break;
        case '6':
          intGrid =6;
          break;
        case '7':
          intGrid =7;
          break;
        case '8':
          intGrid =8;
          break;
        }
        cellsum += intGrid;
      }
    }
  }
  return cellsum;
}


// Generates a minesweeper board of size (mxn) with randomly generated mines and values based on the number of mines touching a cell(A)
char **makenewboard(int m, int n, int mines) {
  
  char **grid = (char **)malloc(m * sizeof(char *));
  int i, j, a, b; 
  int minestouched = 0;

  for (i = 0; i < m; i++) {
    grid[i] = (char *)malloc(n * sizeof(char));
  }
  srand(time(0));

  // Mark all cells as empty'E'/(A)
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      grid[i][j] = 'E';
    }
  }

  // Generates positions randomly and marks them M(A)
  for (i = 0; i < floor(mines / 2); i++) {
    a = rand() % m;
    b = rand() % n;
    grid[a][b] = 'M';
    // generates mine position till its unique[unoccupied](A)
    while (grid[a][b] == 'M') {
      a = rand() % m;
      b = rand() % n;
      if (grid[a][b] != 'M') {
        break;
      }
    }
    grid[a][b] = 'M';
  }

  // Gives each cell a value which is equal to number of mines the cell is
  // touching(A)
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {

      // Edge cell1/(A)
      if (i == 0 && j == 0 && grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j + 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }
      }
      // Edge cell2/(A)
      else if (i == 0 && j == n - 1 && grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j - 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }
      }
      // Edge cell3/(A)
      else if (i == m - 1 && j == 0 && grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i - 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j + 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }
      }
      // Edge cell4/(A)
      else if (i == m - 1 && j == n - 1 && grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i - 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j - 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }
      }

      // Side1 excl. edges/(A)
      else if (i == 0 && j != 0 && j != n - 1 && grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j + 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }

      }
      // Side2 excl. edges/(A)
      else if (i == m - 1 && j != 0 && j != n - 1 && grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j + 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }
      }
      // Side3 excl. edges/(A)
      else if (i != 0 && i != m - 1 && j == 0 && grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i - 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j + 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }
      }
      // Side4 excl. edges/(A)
      else if (i != 0 && i != m - 1 && j == n - 1 && grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i - 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j - 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }
      }

      // Cells not on edges or sides/(A)
      else if (grid[i][j] == 'E') {
        minestouched = 0;
        if (grid[i - 1][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i - 1][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i][j - 1] == 'M') {
          minestouched++;
        }
        if (grid[i][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j + 1] == 'M') {
          minestouched++;
        }
        if (grid[i + 1][j - 1] == 'M') {
          minestouched++;
        }

        if (('0' + minestouched) != '0') {
          grid[i][j] = '0' + minestouched;
        } else {
          grid[i][j] = 'E';
        }
      }
    }
  }  
  return grid;
}


// Function to check if the Minesweeper game is won (S)
int gamewin(char **revealedgrid, char **hiddengrid, int m, int n) {
  int i,j;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      // Check if a non-mine cell is hidden
      if (revealedgrid[i][j] != 'M' && hiddengrid[i][j] == '*') {
        return 0; // Game is not win yet
      }
    }
  }
  return 1; // All non-mine cells are revealed, game is win
}


// Function to print the current state of the Minesweeper game(S)
void printgamestate(char **revealedgrid, char **hiddengrid, int m, int n, int score, int level, int totalmines, int cellsum) {

  // // TEST CODE to be removed after development
  // printf("\nRevealed Grid:\n");
  // for (int i = 0; i < m; i++) {
  //   for (int j = 0; j < n; j++) {
  //     printf("%c ", revealedgrid[i][j]);
  //   }
  //   printf("\n");
  // }

  printf("\nHidden Grid:\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%c ", hiddengrid[i][j]);
    }
    printf("\n");
  }
  //Score to be modified according to density of mines and time consumed then printed (P)
  float fcs = (float)cellsum;
  float ftm = (float)totalmines;
  float s = (float)ftm/fcs;
  printf("Score: %.2f\n",(score*((s)*100)));
}


// Reveal surrounding of a cell(A)
void revealsurround(char **revealedgrid, char **hiddengrid, int m, int n,int x, int y){
  if(y-1 >= 0  ){
    if(revealedgrid[y-1][x] != 'M'){
      hiddengrid[y-1][x] = revealedgrid[y-1][x];
    }
  }

  if(y+1 <= m-1  ){
    if(revealedgrid[y+1][x] != 'M'){
      hiddengrid[y+1][x] = revealedgrid[y+1][x];
    }
  }

  if(x-1 >= 0 ){
    if(revealedgrid[y][x-1] != 'M'){
      hiddengrid[y][x-1] = revealedgrid[y][x-1];
    }
  }

  if(x+1 <= n-1 ){
    if(revealedgrid[y][x+1] != 'M'){
      hiddengrid[y][x+1] = revealedgrid[y][x+1];
    }
  }
}



int main() {
  int m, n, i, j, x, y;
  int a,b;
  int level;
  srand(time(0));
  // Input value of m (A)
  printf("Enter value of m for size of board(m x n)[3<=m<=100]: ");
  scanf("%d", &m);
  while (m < 3 || m > 100) {
    printf("Error!! Reenter value of m for size of board(m x n)[3<=m<=100]: ");
    scanf("%d", &m);
  }

  // Input value of n(A)
  printf("Enter value of n for size of board(m x n)[3<=n<=100]: ");
  scanf("%d", &n);
  while (n < 3 || n > 100) {
    printf("Error!! Renter value of n for size of board(m x n)[3<=n<=100]: ");
    scanf("%d", &n);
  }

  // Input Difficulty Level(A)
  printf("\n1-Easy\n2-Intermediate\n3-Expert\nChoose Level Number: ");
  scanf("%d", &level);
  while (level != 1 && level != 2 && level != 3) {
    printf("\nError!! Reenter Level: ");
    scanf("%d", &level);
  }

  int totalmines = calculatemines(m, n, level), score = 0, temp=0;//(P)
  
  char **revealedgrid = makenewboard(m, n, totalmines); // create new 2d grid(A)

  int cellsum = sumcells(revealedgrid, m, n); //(P)
  
  // initiallize and allocate memory to hidden grid pointer (S)
  char **hiddengrid = (char**)malloc(m * sizeof(char*));
  for (i = 0; i < m; i++) {
    hiddengrid[i] = (char*)malloc(n * sizeof(char));
  }

  // set all elements of hiddengrid to *(S)
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      hiddengrid[i][j] = '*';
    }
  }
  
  // Randomly Reveal a non mined cell and its surroundings(A)
  a = rand() % m;
  b = rand() % n;
  while(revealedgrid[a][b] == 'M'){
    a = rand() % m;
    b = rand() % n;
    if(revealedgrid[a][b] != 'M'){
      break;
    }
  }
  hiddengrid[a][b] = revealedgrid[a][b];
  revealsurround(revealedgrid, hiddengrid,m,n,a,b);

  //(S)
  printgamestate(revealedgrid, hiddengrid, m,n, score, level, totalmines, cellsum);
  
  // Game Loop
  int gameover = 0;
  while (!gameover) {

    // Prompt the user for their move(S)
    printf("Enter x and y coordinates to reveal (e.g. '4 5'): ");
    scanf("%d %d", &x, &y);

    // Check if the input coordinates are valid(S)
    while (x < 0 || x >= m || y < 0 || y >= n) {
      printf("Invalid coordinates. Please enter valid coordinates.\n");
      scanf("%d %d", &x, &y);
    }
    // Check if Mine is revealed(S)
    if (revealedgrid[y][x] == 'M') {
      hiddengrid[y][x] = revealedgrid[y][x]; //reveal mine
      printgamestate(revealedgrid, hiddengrid, m,n,score, level,totalmines,cellsum);//(S)
      printf("Sorry! You lost.\n");
      break;
    }
    else if (hiddengrid[y][x] != '*') {
      // Check if the selected cell has already been revealed(S)
        printf("This cell has already been revealed. Choose another cell.\n");
      }
    else {
      //Update score(P)
      
      temp = calculateScore(score,revealedgrid,hiddengrid,x,y);
      score+=temp;
    }
    
    
    // Update the hidden grid based on the revealed[og] grid(S)
    hiddengrid[y][x] = revealedgrid[y][x];

    //Reveal surrounding hidden cells if not mined(A)
    revealsurround(revealedgrid, hiddengrid,m,n,x,y);
    

    // Display the current state of the game(S)
    printgamestate(revealedgrid, hiddengrid, m, n, score, level,totalmines,cellsum);

    gameover = 0; // Indicate that the game is still ongoing

    // Check if game Won(S)
    if (gamewin(revealedgrid, hiddengrid, m, n)) {
      printf("Congratulations! You won!\n");
      break;
    }
    
  }

  
  // Compare the current score with the highest score and update if necessary (P)
   float fcs = (float)cellsum;
    float ftm = (float)totalmines;
    float s = (float)ftm/fcs;
  int scoreVal = (score*((s)*100));

  
  float highestScore = readHighestScore();
  if (scoreVal > highestScore) {
    float highestScore = scoreVal;
    
    printf("Congratulations! You achieved a new high score: %.2f\n", highestScore);
    writeHighestScore(highestScore);
  }
  // free space(A)
  free2DArray(revealedgrid, m);
  free2DArray(hiddengrid, m);
}