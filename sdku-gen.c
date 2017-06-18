#include <stdio.h>
#include <stdlib.h>

#define X_DIM 9
#define Y_DIM X_DIM

#define SDKU_SIZE (X_DIM * Y_DIM)


/* this function takes three arguments, the `__sdku` puzzle 
 * and it's two dimenstion `__ydim` and `__xdim`. in order
 * to print the puzzle on the screen. */
int printsdku(int **__sdku, int __ydim, int __xdim);

/* this function takes two arguments; which represents the 
 * `__ydim` and `__xdim` dimensions of the Sudoku puzzle.
 *
 * the puzzle is represented with a 2-dim-array, so this 
 * function allocates and returns an `int **`. */
int **initsdku(int __ydim, int __xdim);

/* this function takes three arguments; the `__sdku` puzzle
 * and its dimesions `__ydim` and `__xdim`. 
 * it frees (dis-allocate) `__sdku` from the memory */
int freesdku(int **__sdku, int __ydim, int __xdim);

int main()
{
  int **s = initsdku(Y_DIM, X_DIM);

  printsdku(s, Y_DIM, X_DIM);
  
  freesdku(s, Y_DIM, X_DIM);
  
  return 0;
}

int printsdku(int **sdku, int __y, int __x)
{
  for(int y = 0; y < __y; ++y) { 
    for(int x = 0; x < __x; ++x)
      printf(" %d ", sdku[y][x]);
    putchar('\n');
  }

  return 0;
}

int **initsdku(int __y, int __x)
{
  /* there must be another way to allocate memory 
   * using a single line instruction. */
  int **sdku = (int **) malloc(__y * sizeof(int *));
  
  for(int y = 0; y < __y; ++y) {
    sdku[y] = (int *) malloc(__x * sizeof(int));
      for(int x = 0; x < __x; ++x) sdku[y][x] = 0;
  }

  return sdku;
}

int freesdku(int **sdku, int __y, int __x)
{
  for(int y = 0; y < __y; ++y) {
    for(int x = 0; x < __x; ++x)
      sdku[y][x] = 0;		/* i am not sure that this is
				 * required but it looks that
				 * it has no effect.. */
    free(sdku[y]);
  }

  free(sdku);
  
  return 0;
}
