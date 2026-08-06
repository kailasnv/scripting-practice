#include <stdio.h>
#include <unistd.h>

/* display */
#define HEIGHT 8
#define WIDTH 8
char screen[HEIGHT][WIDTH]; // 2d array
int birdX = 1;              // bird position
int birdY = 1;

/* game vaiables */
int gameOver = 0;
int score = 0;

int kbhit() {
  char ch;

  if (read(STDIN_FILENO, &ch, 1) > 0)
    return ch;

  return 0;
}

int jump() {}

int main() {

  // game loop
  while (!gameOver) {

    // draw bird
    screen[birdY][birdX] = 'O';
    // add gravity
    birdY++;
    if (birdY >= HEIGHT) {
      gameOver = 1;
    }
    // jump bird
    int key = kbhit();
    if (key = ' ')
      jump();
    if (key = 'q')
      break;

    // draw pip

    // move pipe

    // collision

    // render all
    printf("\033[2J"); // clears terminal
    printf("\033[H");  // resets teh cursor to topleft

    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        printf("%c", screen[y][x]);
      }
      printf("\n");
    }
    printf("\nScore: %d\n", score);
    printf("SPACE = Jump   Q = Quit\n");

    usleep(250000); // sleep for 250ms
  } // game loop end
  printf("\nGAME OVER\n");
  return 0;
}
