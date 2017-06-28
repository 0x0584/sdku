#include "../include/sdku.h"
#include "../include/sdku-alloc.h"

sdku_t * initsdku(int ydim, int xdim)
{  
  sdku_t *foosdku = NULL;

  int xb = xdim/3, yb = ydim/3;

  foosdku = (sdku_t *) malloc(sizeof(sdku_t));

  foosdku->block = initblock(xb, yb); /* the block is 3x3 */

  /* here! */
  /* key-idea: loop over blocks and their cells
  * then for each block, */

  /*
   *   j\i   0   1   2       3   4   5       6   7   8
   *
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   0   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   1   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   2   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *       
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   3   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   4   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   5   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *       
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   6   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   7   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   8   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   */

  node_t *row = (node_t *) malloc(Y_DIM * sizeof(node_t)),
  	*col = (node_t *) malloc(X_DIM * sizeof(node_t));
  
  /* loop over blocks */
  for(int j = 0; j < yb; ++j) 
	for(int i = 0; i < xb; ++i) {
	  /* loop over cells in a block */
	  for(int jj = 0; jj < yb; ++jj) {
		for(int ii = 0; ii < xb; ++ii) {
		  cell_t *c = &(foosdku->block[j][i].grid[jj][ii]);
		  /* + append the current cell to the corresponding
		   *   row-or-column list pR, pC. then set the cell's 
		   *   row-and-column pointers (pR, pC) */
		  c->row = appendto(&(row[getindex(j, i)]), c);
		  c->column = appendto(&(col[getindex(jj, ii)]), c);
	    }
		putchar('\t');
	  }
	  putchar('\n');
	}
  return foosdku;
}


cell_t ** initgrid(int ygrid, int xgrid)
{
  cell_t **foocell = NULL;

  foocell = (cell_t **) malloc(ygrid * sizeof(cell_t *));

  for(int j = 0; j < ygrid; ++j) {
	foocell[j] = (cell_t *) malloc(xgrid * sizeof(cell_t));
	for(int i = 0; i < xgrid; ++i) {
	  foocell[j][i].value = -1;
	  foocell[j][i].row = NULL;
	  foocell[j][i].column = NULL;
	}
  }

  return foocell;
}

block_t ** initblock(int yblock, int xblock)
{
  block_t **fooblock = NULL;

  fooblock = (block_t **) malloc(yblock * sizeof(block_t *));

  for(int j = 0; j < yblock; ++j) {
	fooblock[j] = (block_t *) malloc(xblock * sizeof(block_t));
	for(int i = 0; i < xblock; ++i)
	  fooblock[j][i].grid = initgrid(yblock, xblock);
  }

  return fooblock;
}

node_t * appendto(node_t *head, cell_t *cell)
{
  /* key-idea: append the cell to the last node
   *		   in the head */

  node_t *foo = head;

  /* no head is found */
  if(!(foo)) foo->cell = cell, foo->next = NULL;
  else /* head exists! */ {
	/* move to the end of the list */
	while(foo->next) foo = foo->next;
	/* append the new node */
	foo->cell = cell;
	foo->next = NULL;
  }
  
  return head;
}

int getindex(int y, int x)
{
  /* because of the Sudoku has 9*9 cells (or 3*3 blocks)
   * this hack works! i don't know how it really works! */
  for(int i = y, index = 0;
	  i >= 0;
	  i -= 1, index += 3)
	if(i == 0) return index + x;
}


int freesdku(sdku_t *sdku, int ydim, int xdim)
{
  for(int j = 0; j < ydim/3; ++j) {
	for(int i = 0; i < xdim/3; ++i) {
	  for(int jj = 0; jj < ydim/3; ++jj) {
		for(int ii = 0; ii < xdim/3; ++ii) {
		  if(sdku->block[j][i].grid[jj][ii].row) {
			free(sdku->block[j][i].grid[jj][ii].row);
			sdku->block[j][i].grid[jj][ii].row = NULL;
		  }
		  if(sdku->block[j][i].grid[jj][ii].column) {
			free(sdku->block[j][i].grid[jj][ii].column);
			sdku->block[j][i].grid[jj][ii].column = NULL;
		  }
		}
		free(sdku->block[j][i].grid[jj]);
	  }
	}
	free(sdku->block[j]);
  }

  free(sdku->block);
  free(sdku);

  return 0;
}
