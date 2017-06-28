#ifndef _SDKU_ALLOC_H
#define SDKU_ALLOC_H
#include "types.h"

block_t ** initblock(int, int);
cell_t ** initgrid(int, int);
node_t * appendto(node_t *, cell_t *);
int getindex(int, int);

/* this function takes two arguments; which represents the 
 * `__ydim` and `__xdim` dimensions of the Sudoku puzzle.
 *
 * the puzzle is represented with a 2-dim-array, so this 
 * function allocates and returns an `int **`. */
sdku_t * initsdku(int __ydim, int __xdim);

/* this function takes three arguments; the `__sdku` puzzle
 * and its dimesions `__ydim` and `__xdim`. 
 * it frees (dis-allocate) `__sdku` from the memory */
int freesdku(sdku_t * __sdku, int __ydim, int __xdim);

#endif
