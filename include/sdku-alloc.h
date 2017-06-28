#ifndef _SDKU_ALLOC_H
#define SDKU_ALLOC_H
#include "types.h"

block_t ** initblock(int __blck_ydim, int __blck_xdim);
cell_t ** initgrid(int __grid_ydim, int __grid_xdim);
node_t * appendto(node_t *__head, cell_t *__cell);

/* IDEA: this hack works because the Sudoku has 3*3 blocks
 *		 each block has 3*3 cells. when tracking block's 
 *		 coordinates we actually track the row. when we
 *		 when we track the 
 *
 *
 * RET:	 I: when passing the (Y, X) of a block, it returns
 *		    the index of the row of that cell 
 *		II: when passing the (Y', X') of a cell, it returns 
 *			the index of the column of that cell
 */
/*					j			  i     */
int getindex(int __yindex, int __xindex);

/* this function takes two arguments; which represents the 
 * `__ydim` and `__xdim` dimensions of the Sudoku puzzle.
 *
 * the puzzle is represented with a 2-dim-array, so this 
 * function allocates and returns an `int **`. */
sdku_t * initsdku(int __ydim, int __xdim);

/* this function takes three arguments; the `__sdku` puzzle
 * and its dimesions `__ydim` and `__xdim`. 
 * it frees (dis-allocate) `__sdku` from the memory */
int freesdku(sdku_t *__sdku, int __ydim, int __xdim);

#endif
