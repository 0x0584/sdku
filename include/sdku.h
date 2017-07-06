#ifndef _SDKU_H
#define _SDKU_H

#define Y_DIM 9
#define X_DIM Y_DIM

#define FRESH_CELL (-1)

#define MIN_SCR_Y 24
#define MIN_SCR_X 56

#include "types.h"

#include <ncurses.h>
#include <stdlib.h>

#include <string.h>

#include <time.h>

/* represents a puzzle of blocks; the Sudoku puzzle */
struct _SUDOKU_PUZZLE_STRUCT {
  /* represents an individual block of cells */
  struct _SUDOKU_BLOCK_STRUCT {
	/* represents an individual cell */
	struct _SUDOKU_CELL_STRUCT {
	  /* represents an individual row or column */
	  struct _LINKED_LIST_STRUCT {
		cell_t *cell;			/* current cell in row/column */
		node_t *next;			/* next cell in row/column */
	  } *row, *column; 
	  int value;				/* value of the cell */
	} **grid;					/* block of cells (3x3) */
  } **block;					/* puzzle of blocks (3x3) */
};

/* this function takes three arguments, the `__sdku` puzzle 
 * and it's two dimenstion `__ydim` and `__xdim`. in order
 * to print the puzzle on the screen. */
int printsdku(sdku_t *__sdku, int __ydim, int __xdim);
#define putsdku(s) printsdku(s, Y_DIM, X_DIM)

/* this function generates a Sudoku */
sdku_t * gensdku(int __ydim, int __xdim);

extern int MAX_ROWS, MAX_COLUMNS;
#endif	/* _SDKU_H */
