/* TODO: REWRITE FUNCTIONS! */

/*  AUTHOR: Anas Rchid <rchid.anas@gmail.com>
 *   ABOUT: this is a program that generates a standard
 *          9x9 Sudoku puzzle 
 * CREATED: 06/18/2017
 */

/* -------------------------------- HEADERS -------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define X_DIM 9
#define Y_DIM X_DIM

/* -------------------- STRUCTURE-TYPES AND ENUMERATIONS -------------------- */
#ifndef __cpluslpus
typedef enum _BOOL_TYPE { false = (1==0), true = !false } bool;
#endif

typedef int * row_t;
typedef int * clmn_t;
typedef struct _SUDOKU_CELL_STRUCT * cell_t;
typedef struct _SUDOKU_BLOCK_STRUCT * block_t;
typedef struct _SUDOKU_PUZZLE_STRUCT * sdku_t;

struct _SUDOKU_CELL_STRUCT {
  bool isvisited;
  int value;
  row_t row;
  clmn_t column;
};

struct _SUDOKU_BLOCK_STRUCT {
  cell_t gride[3];		/* this is would hold 3x3 */
};
/* ------------------------------- PROTOTYPES ------------------------------- */

/* this function takes three arguments, the `__sdku` puzzle 
 * and it's two dimenstion `__ydim` and `__xdim`. in order
 * to print the puzzle on the screen. */
int printsdku(int **__sdku, int __ydim, int __xdim);

/* this function takes two arguments; which represents the 
 * `__ydim` and `__xdim` dimensions of the Sudoku puzzle.
 *
 * the puzzle is represented with a 2-dim-array, so this 
 * function allocates and returns an `int **`. */
static int ** initsdku(int __ydim, int __xdim);

/* this function */
int ** gensdku(cell_t **__sdku, int __ydim, int __xdim);

/* this function takes three arguments; the `__sdku` puzzle
 * and its dimesions `__ydim` and `__xdim`. 
 * it frees (dis-allocate) `__sdku` from the memory */
int freesdku(int **__sdku, int __ydim, int __xdim);

int main()
{
  srand(time(NULL));
  
  int **s = initsdku(Y_DIM, X_DIM);

  printsdku(s, Y_DIM, X_DIM);
  
  freesdku(s, Y_DIM, X_DIM);
  
  return 0;
}

int printsdku(int **sdku, int __y, int __x)
{
  if(!sdku) goto FAILURE;
  
  for(int y = 0; y < __y; ++y) {
    for(int x = 0; x < __x; ++x)
      printf("| %d ", sdku[y][x]);
    putchar('|');
    putchar('\n');
  }

  return 0;

 FAILURE: return -1;
}

static int ** initsdku(int __y, int __x)
{
  /* there must be another way to allocate memory 
   * using a single line instruction. */
  int **sdku = NULL;

  if((sdku = (int **) malloc(__y * sizeof(int *))))
    goto FAILURE;
     
  for(int y = 0; y < __y; ++y) {
    if((sdku[y] = (int *) malloc(__x * sizeof(int))))
      goto FAILURE;
    for(int x = 0; x < __x; ++x) sdku[y][x] = FRESH_CELL;
  }

  return gensdku(sdku, __y, __x);

 FAILURE:
  free(sdku);
  return NULL;
}

int ** gensdku(cell_t **sdku, int __y, int __x)
{
  int value[9] = {};	    /* regenerated everytime we fill a cell */

  /* key-idea: take a number from the `value` array and store
   * it in a foo-variable. take the next unvisited-cell 
   * (starting at cell-0,0). make sure that the number does not
   * appear twice:
   *
   *	+ in the same row    : y-axis
   *	+ in the same column : x-axis
   *	+ in the same block  : the square is 3x3
   *
   * # in the same row: bool isinrow(row, value)
   *
   * we have saved the pointer of the row in a variable.
   * it's the cell's row
   * 
   * check the row to see if it already has a value similar
   * to foo-variable. if so, take the next-value and store
   *    if in the foo-variable, and repeat the process 
   * recursively until our condition, isinrow emains false.
   *
   *	RET: the value
   * 
   * then, keep going through the column and the block
   * 
   * # in the same column: bool isincolumn(column, value)
   * # in the same block: bool isinblock(block, value)
   * 
   * the same treatment as the isinrow except passing the
   * column, indeed the block of cells too instead of the row
   * 
   * the order of checking is the following:
   *
   *	1. row
   *	2. column
   *	3. block
   * 
   * the three of those must return true, in order to fill 
   * a cell, otherwise chose the next-value from values and
   * store it in foo-variable. repeat the whole treatment;
   * recursively. until all the array is filled.
   */
  
  for(int y = 0; y < __y; ++y) {
    for(int x = 0; x < __x; ++x) {
      if(sdku[y][x]->isvisited == true) {
	sdku[y][x] = rand()%__y;
      } else {
	
      }
    }
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
