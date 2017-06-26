#ifndef _SDKU_H
#define _SDKU_H

#define Y_DIM 9
#define X_DIM Y_DIM

#include "types.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

/* represents an puzzle of blocks; the Sudoku puzzle */
struct _SUDOKU_PUZZLE_STRUCT {
  /* represents an individual block of cells */
  struct _SUDOKU_BLOCK_STRUCT {
	/* represents an individual cell */
	struct _SUDOKU_CELL_STRUCT {
	  cell_t *row,				/* row of this cell */
		*column;				/* column of this cell */
	  int value;				/* value of the cell */
	} **grid;					/* block of cells (3x3) */
  } **block;					/* puzzle of blocks (3x3) */
};

/* this function takes three arguments, the `__sdku` puzzle 
 * and it's two dimenstion `__ydim` and `__xdim`. in order
 * to print the puzzle on the screen. */
int printsdku(sdku_t *__sdku, int __ydim, int __xdim);
#define putsdku(s) printsdku(s, Y_DIM, X_DIM)

/* this function takes two arguments; which represents the 
 * `__ydim` and `__xdim` dimensions of the Sudoku puzzle.
 *
 * the puzzle is represented with a 2-dim-array, so this 
 * function allocates and returns an `int **`. */
sdku_t * initsdku(int __ysdku_dim, int __xsdku_dim);

/* this function generates a Sudoku */
sdku_t * gensdku(sdku_t * __sdku, int __ydim, int __xdim);

/* this function takes three arguments; the `__sdku` puzzle
 * and its dimesions `__ydim` and `__xdim`. 
 * it frees (dis-allocate) `__sdku` from the memory */
int freesdku(sdku_t * __sdku, int __ydim, int __xdim);

#endif	/* _SDKU_H */
